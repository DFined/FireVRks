// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ParameterIntegration/v2/EffectSystemSavingWidget.h"

#include "ImageUtils.h"
#include "Components/EditableText.h"
#include "Components/Image.h"
#include "Components/MultiLineEditableTextBox.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/SizeBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/WidgetSwitcher.h"
#include "Components/WidgetSwitcherSlot.h"
#include "DFUI/DFStyleUtil.h"
#include "DFUI/DFUI.h"
#include "FX/Niagara/Scheduler/EffectSpawnCoordinator.h"
#include "FX/Niagara/v2/MapParameterValueContext.h"
#include "FX/Niagara/v2/System/EffectSystemManager.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Serialization/BufferArchive.h"
#include "Slate/SlateBrushAsset.h"
#include "Util/DFStatics.h"
#include "Util/FileHelper.h"

void UEffectSystemSavingWidget::Save()
{
	UEffectSystemManager::GetInstance()->SaveEffect(System);
}

void UEffectSystemSavingWidget::ChooseIcon()
{
	Viewport->SetBrushFromAsset(UDFStatics::EFFECT_TESTING_SLATE_BRUSH);
	
	IconSelectSwitcher->SetActiveWidgetIndex(1);

	UDFStatics::EFFECT_SPAWN_COORDINATOR->SpawnEffect(ULaunchSettings::Make(this, System, UMapParameterValueContext::Instance(this), nullptr, 0, 0, 0, 0));
}

void UEffectSystemSavingWidget::FinishSavingIcon()
{
	auto IconsPath = UFileHelper::GetInstance()->GetIconsContentPath();
	
	FImage Image = FImage();
	FImageUtils::GetRenderTargetImage(RenderTarget, Image);
	// Theres probably a better way to do this, and if so, I'd love to know. But for some reason, UE inverts the alpha channel when exporting a render target
	// so we need to invert it right back to get a usable image
	for (int i = 3; i < Image.RawData.Num(); i+=4)
	{
		Image.RawData[i] = 255 - Image.RawData[i];
	}
	FString IconPath = FPaths::Combine(IconsPath, System->GetId().GetId() + ".png");
	FImageUtils::SaveImageByExtension(*IconPath, Image, 0);

	System->SetIcon(UIcon::New(System, IconPath, false));

	Viewport->SetBrushFromTexture(DFStyleUtil::LoadCachedTexture(System->GetIcon()));
	IconSelectSwitcher->SetActiveWidgetIndex(0);
}

void UEffectSystemSavingWidget::CancelSavingIcon()
{
	Viewport->SetBrushFromTexture(DFStyleUtil::LoadCachedTexture(System->GetIcon()));
	IconSelectSwitcher->SetActiveWidgetIndex(0);
}

UPanelWidget* UEffectSystemSavingWidget::MakeRootWidget()
{
	RootBorder = DFUI::MakeWidget<UBorder>(this);
	DFStyleUtil::BasicBorderStyle(RootBorder, DFStyleUtil::GREY_LVL_3);

	RootBox = DFUI::AddWidget<UVerticalBox>(RootBorder);
	SystemNameInput = DFUI::NamedWidget<UEditableTextBox>(RootBox, "System name");
	DFStyleUtil::TextBoxStyle(SystemNameInput);
	AuthorInput = DFUI::NamedWidget<UEditableTextBox>(RootBox, "Author");
	DFStyleUtil::TextBoxStyle(AuthorInput);
	DescriptionInput = DFUI::NamedWidget<UMultiLineEditableTextBox>(RootBox, "Description");
	DFStyleUtil::TextAreaStyle(DescriptionInput);

	auto VPWrapper = DFUI::AddWidget<USizeBox>(this);
	auto IconStacker = DFUI::AddWidget<UOverlay>(VPWrapper);
	Viewport = DFUI::AddWidget<UImage>(IconStacker);
	VPWrapper->SetMinAspectRatio(1);
	VPWrapper->SetMaxAspectRatio(1);
	VPWrapper->SetWidthOverride(768);
	VPWrapper->SetHeightOverride(768);
	VPWrapper->SetMinDesiredWidth(768);
	if (auto SizeSlot = Cast<UVerticalBoxSlot>(VPWrapper->Slot))
	{
		SizeSlot->SetPadding(FMargin(15));
		SizeSlot->SetHorizontalAlignment(HAlign_Center);
		SizeSlot->SetVerticalAlignment(VAlign_Center);
	}

	IconSelectSwitcher = DFUI::AddWidget<UWidgetSwitcher>(IconStacker);
	if (auto StackerSlot = Cast<UOverlaySlot>(Viewport->Slot))
	{
		StackerSlot->SetHorizontalAlignment(HAlign_Fill);
		StackerSlot->SetVerticalAlignment(VAlign_Fill);
	}

	auto ChangeIconBtn = DFUI::AddButton(IconSelectSwitcher, "Change icon");
	DFStyleUtil::SafeSetSlotAlignment<UWidgetSwitcherSlot>(ChangeIconBtn->Slot, HAlign_Fill, VAlign_Center);
	ChangeIconBtn->OnPressed.AddUniqueDynamic(this, &UEffectSystemSavingWidget::ChooseIcon);

	auto IconToolbox = DFUI::AddWidget<UHorizontalBox>(IconSelectSwitcher);
	DFStyleUtil::SafeSetSlotAlignment<UWidgetSwitcherSlot>(IconToolbox->Slot, HAlign_Fill, VAlign_Top);
	auto SaveIconBtn = DFUI::AddButtonToButtonPanel(IconToolbox, "Save Icon");
	SaveIconBtn->OnPressed.AddUniqueDynamic(this, &UEffectSystemSavingWidget::FinishSavingIcon);
	auto CancelIconBtn = DFUI::AddButtonToButtonPanel(IconToolbox, "Cancel");
	CancelIconBtn->OnPressed.AddUniqueDynamic(this, &UEffectSystemSavingWidget::CancelSavingIcon);
	IconSelectSwitcher->SetActiveWidgetIndex(0);

	ResultBox = DFUI::AddWidget<UHorizontalBox>(this);
	auto OkBtn = DFUI::AddButtonToButtonPanel(ResultBox, "Save");
	OkBtn->OnPressed.AddUniqueDynamic(this, &UEffectSystemSavingWidget::Save);

	auto CancelBtn = DFUI::AddButtonToButtonPanel(ResultBox, "Cancel");
	return RootBorder;
}


UPanelWidget* UEffectSystemSavingWidget::GetMountingPoint()
{
	return RootBox;
}

void UEffectSystemSavingWidget::SetMeta(UCustomEffectSystem* Meta)
{
	System = Meta;
	SystemNameInput->SetText(FText::FromString(Meta->GetDisplayName()));
	AuthorInput->SetText(FText::FromString(Meta->GetAuthor()));
	DescriptionInput->SetText(FText::FromString(Meta->GetDescription()));
	Viewport->SetBrushFromTexture(DFStyleUtil::LoadCachedTexture(System->GetIcon()));
}

void UEffectSystemSavingWidget::SetRenderTarget(UTextureRenderTarget2D* bRenderTarget)
{
	this->RenderTarget = bRenderTarget;
}
