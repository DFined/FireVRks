// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ParameterIntegration/v2/ParameterBindingSetupUI.h"

#include "Components/Spacer.h"
#include "FX/Niagara/v2/BindingParameterValueContext.h"
#include "FX/Niagara/v2/System/SubsystemConfig.h"
#include "DFUI/DFUI.h"
#include "UI/Icons.h"
#include "UI/CoreUI/EffectEditorUI.h"
#include "UI/ParameterIntegration/v2/ParameterRenderer.h"
#include "UI/ParameterIntegration/v2/SystemDisplayTile.h"
#include "Util/DFStatics.h"

void UParameterBindingSetupUI::Delete()
{
	this->RemoveFromParent();
	auto CustomSystem = DFU::AttemptFindObjectByType<UCustomEffectSystem>(SubsystemConfig);
	CustomSystem->GetSubsystemConfig().Remove(SubsystemConfig);
}


void UParameterBindingSetupUI::MoveUp()
{
	auto Editor = DFUI::AttemptFindWidgetByType<UEffectEditorUI>(this);
	Editor->MoveSystemUp(this);
}

void UParameterBindingSetupUI::MoveDown()
{
	auto Editor = DFUI::AttemptFindWidgetByType<UEffectEditorUI>(this);
	Editor->MoveSystemDown(this);
}

UPanelWidget* UParameterBindingSetupUI::MakeRootWidget()
{
	RootBorder = DFUI::MakeWidget<UBorder>(this);
	DFStyleUtil::BasicBorderStyle(RootBorder, DFStyleUtil::GREY_LVL_2);

	HeaderBox = DFUI::MakeWidget<UHorizontalBox>(this);
	
	auto VBox = DFUI::MakeWidget<UVerticalBox>(this);
	
	DFUI::MakeExpandableTab(RootBorder, HeaderBox, VBox, true);
	
	SystemDisplayTile = DFUI::AddWidget<USystemDisplayTile>(VBox);
	SystemDisplayTile->GetOnSelectionChanged().AddUniqueDynamic(this, &UParameterBindingSetupUI::Setup);

	ParamsBox = DFUI::AddWidget<UVerticalBox>(VBox);
	return RootBorder;
}


void UParameterBindingSetupUI::Setup(UEffectSystem* bSystem)
{
	this->System = bSystem;
	SystemDisplayTile->SetSystem(bSystem);
	ParamsBox->ClearChildren();
	HeaderBox->ClearChildren();
	auto Label = DFUI::AddLabel(HeaderBox, SubsystemConfig->GetSubsystemName());
	DFStyleUtil::SafeSetHBoxSlotWidth(Label->Slot, FSlateChildSize(ESlateSizeRule::Automatic));

	auto Spacer = DFUI::AddWidget<USpacer>(HeaderBox);
	DFStyleUtil::SafeSetHBoxSlotWidth(Spacer->Slot, FSlateChildSize(ESlateSizeRule::Fill));
	
	auto UpBtn = DFUI::AddImageButton(HeaderBox, UDFStatics::ICONS->UP_ICON, 24);
	DFStyleUtil::SafeSetHBoxSlotWidth(UpBtn->Slot, FSlateChildSize(ESlateSizeRule::Automatic));
	UpBtn->OnPressed.AddUniqueDynamic(this, &UParameterBindingSetupUI::MoveUp);
	
	auto DownBtn = DFUI::AddImageButton(HeaderBox, UDFStatics::ICONS->DOWN_ICON, 24);
	DFStyleUtil::SafeSetHBoxSlotWidth(DownBtn->Slot, FSlateChildSize(ESlateSizeRule::Automatic));
	DownBtn->OnPressed.AddUniqueDynamic(this, &UParameterBindingSetupUI::MoveDown);

	auto DelBtn = DFUI::AddImageButton(HeaderBox, UDFStatics::ICONS->DELETE_ICON, 24);
	DelBtn->OnPressed.AddUniqueDynamic(this, &UParameterBindingSetupUI::Delete);
	DFStyleUtil::SafeSetHBoxSlotWidth(DelBtn->Slot, FSlateChildSize(ESlateSizeRule::Automatic));
	auto Context = UBindingParameterValueContext::New(SubsystemConfig);
	Context->SetBindings(SubsystemConfig->GetBindings());
	auto OuterParams = TArray<UAbstractFormalParameter*>();
	System->GetOuterParametersInOrder(OuterParams);
	for (auto Param : OuterParams)
	{
		UParameterRenderer::RenderParam(this, Context, Param, INNER_SYSTEM_BINDING);
	}
}

void UParameterBindingSetupUI::SetSystem(UEffectSystem* bSystem)
{
	System = bSystem;
}

UPanelWidget* UParameterBindingSetupUI::GetMountingPoint()
{
	return ParamsBox;
}

UParameterBindingSetupUI* UParameterBindingSetupUI::InstanceFrom(UPanelWidget* Parent, UEffectSystem* System, USubsystemConfig* Bindings)
{
	auto SetupUI = DFUI::AddWidget<UParameterBindingSetupUI>(Parent);
	SetupUI->SubsystemConfig = Bindings;
	SetupUI->Setup(System);
	return SetupUI;
}
