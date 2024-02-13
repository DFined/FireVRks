// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DFInputPopup.h"

#include "Components/Border.h"
#include "Components/BorderSlot.h"
#include "Components/VerticalBox.h"
#include "DFUI/DFUI.h"

UPanelWidget* UDFInputPopup::MakeRootWidget()
{
	RootBox = DFUI::MakeWidget<UVerticalBox>(this);
	return RootBox;
}

UPanelWidget* UDFInputPopup::GetMountingPoint()
{
	return RootBox;
}

void UDFInputPopup::Confirm()
{
	OnConfirm.Broadcast(this->InputWidget);
	this->RemoveFromParent();
}

void UDFInputPopup::Cancel()
{
	OnCancel.Broadcast();
	this->RemoveFromParent();
}

void UDFInputPopup::InitializePopup(UWidget* Input, FString TooltipText)
{
	auto BaseBorder = DFUI::AddWidget<UBorder>(RootBox);
	auto RootBorder = DFUI::AddWidget<UBorder>(BaseBorder);
	DFStyleUtil::RoundedBorderStyle(BaseBorder, DFStyleUtil::GREY_LVL_3, 10);
	DFStyleUtil::RoundedBorderStyle(RootBorder, DFStyleUtil::GREY_LVL_2, 10);
	DFStyleUtil::SetPadding<UBorderSlot>(RootBorder, FMargin(5, 5, 5, 5));

	DFStyleUtil::SafeSetVBoxSlotAlignment(BaseBorder->Slot, HAlign_Center);
	DFStyleUtil::SafeSetVBoxSlotWidth(BaseBorder->Slot, FSlateChildSize(ESlateSizeRule::Fill));

	auto VBox = DFUI::AddWidget<UVerticalBox>(RootBorder);
	auto Text = DFUI::AddWidget<UTextBlock>(VBox);
	Text->SetText(FText::FromString(TooltipText));
	DFStyleUtil::SafeSetVBoxSlotAlignment(Text->Slot, HAlign_Center);
	DFStyleUtil::TextBlockStyle(Text);

	InputWidget = Input;
	VBox->AddChildToVerticalBox(Input);
	DFStyleUtil::SafeSetVBoxSlotAlignment(InputWidget->Slot, HAlign_Center);

	auto HBox = DFUI::AddWidget<UHorizontalBox>(VBox);
	DFStyleUtil::SafeSetVBoxSlotAlignment(HBox->Slot, HAlign_Center);
	auto OkBtn = DFUI::AddWidget<UButton>(HBox);
	auto CancelBtn = DFUI::AddWidget<UButton>(HBox);

	auto OkText = DFUI::MakeWidget<UTextBlock>(this);
	OkText->SetText(FText::FromString("Ok"));
	OkBtn->SetContent(OkText);
	OkBtn->OnPressed.AddUniqueDynamic(this, &UDFInputPopup::Confirm);

	DFStyleUtil::TextBlockStyle(OkText);
	DFStyleUtil::TextButtonStyle(OkBtn, DFStyleUtil::GREY_LVL_2);

	auto CancelText = DFUI::MakeWidget<UTextBlock>(this);
	CancelText->SetText(FText::FromString("Cancel"));
	CancelBtn->SetContent(CancelText);
	DFStyleUtil::TextBlockStyle(CancelText);
	DFStyleUtil::TextButtonStyle(CancelBtn, DFStyleUtil::GREY_LVL_2);
	CancelBtn->OnPressed.AddUniqueDynamic(this, &UDFInputPopup::Cancel);
}
