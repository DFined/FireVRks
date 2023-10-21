// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DFInputPopup.h"

#include "Components/VerticalBox.h"
#include "UI/DFUIUtil.h"

UPanelWidget* UDFInputPopup::MakeRootWidget(UWidgetTree* Tree)
{
	RootBox = UDFUIUtil::MakeWidget<UVerticalBox>(Tree);
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
	auto BaseBorder = UDFUIUtil::AddWidget<UBorder>(WidgetTree, RootBox);
	auto RootBorder = UDFUIUtil::AddWidget<UBorder>(WidgetTree, BaseBorder);
	DFStyleUtil::BasicBorderStyle(BaseBorder, ESlateBrushDrawType::Box, DFStyleUtil::GREY_LVL_4);
	DFStyleUtil::BasicBorderStyle(RootBorder, ESlateBrushDrawType::Box, DFStyleUtil::GREY_LVL_3);
	DFStyleUtil::SafeSetVBoxSlotAlignment(BaseBorder->Slot, HAlign_Center);
	DFStyleUtil::SafeSetVBoxSlotWidth(BaseBorder->Slot, FSlateChildSize(ESlateSizeRule::Fill));
	
	auto VBox = UDFUIUtil::AddWidget<UVerticalBox>(WidgetTree, RootBorder);
	auto Text = UDFUIUtil::AddWidget<UTextBlock>(WidgetTree, VBox);
	Text->SetText(FText::FromString(TooltipText));
	DFStyleUtil::SafeSetVBoxSlotAlignment(Text->Slot, HAlign_Center);
	DFStyleUtil::TextBlockStyle(Text);

	InputWidget = Input;
	VBox->AddChildToVerticalBox(Input);
	DFStyleUtil::SafeSetVBoxSlotAlignment(InputWidget->Slot, HAlign_Center);
	
	auto HBox = UDFUIUtil::AddWidget<UHorizontalBox>(WidgetTree, VBox);
	DFStyleUtil::SafeSetVBoxSlotAlignment(HBox->Slot, HAlign_Center);
	auto OkBtn = UDFUIUtil::AddWidget<UButton>(WidgetTree, HBox);
	auto CancelBtn = UDFUIUtil::AddWidget<UButton>(WidgetTree, HBox);

	auto OkText = UDFUIUtil::MakeWidget<UTextBlock>(WidgetTree);
	OkText->SetText(FText::FromString("Ok"));
	OkBtn->SetContent(OkText);
	OkBtn->OnPressed.AddUniqueDynamic(this, &UDFInputPopup::Confirm);
	
	DFStyleUtil::TextBlockStyle(OkText);
	DFStyleUtil::TextButtonStyle(OkBtn, DFStyleUtil::GREY_LVL_2);

	auto CancelText = UDFUIUtil::MakeWidget<UTextBlock>(WidgetTree);
	CancelText->SetText(FText::FromString("Cancel"));
	CancelBtn->SetContent(CancelText);
	DFStyleUtil::TextBlockStyle(CancelText);
	DFStyleUtil::TextButtonStyle(CancelBtn, DFStyleUtil::GREY_LVL_2);
	CancelBtn->OnPressed.AddUniqueDynamic(this, &UDFInputPopup::Cancel);
}
