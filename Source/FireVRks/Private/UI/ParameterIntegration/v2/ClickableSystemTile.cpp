// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ParameterIntegration/v2/ClickableSystemTile.h"

#include "Components/Image.h"
#include "UI/DFUIUtil.h"

void UClickableSystemTile::OnClick()
{
	OnSystemPressed.Broadcast(this);
}

UPanelWidget* UClickableSystemTile::MakeRootWidget(UWidgetTree* Tree)
{
	RootBorder = UDFUIUtil::MakeWidget<UBorder>(Tree);
	DFStyleUtil::RoundedBorderStyle(RootBorder, DFStyleUtil::GREY_LVL_3, 10);

	Button = UDFUIUtil::AddWidget<UButton>(Tree, RootBorder);
	Button->OnPressed.AddUniqueDynamic(this, &UClickableSystemTile::OnClick);
	DFStyleUtil::TextButtonStyle(Button, DFStyleUtil::GREY_LVL_3);
	
	auto Box = UDFUIUtil::MakeWidget<UVerticalBox>(Tree);
	Button->SetContent(Box);
	

	Image = UDFUIUtil::AddWidget<UImage>(Tree, Box);
	Label = UDFUIUtil::AddWidget<UTextBlock>(WidgetTree, Box);
	DFStyleUtil::SafeSetVBoxSlotAlignment(Label->Slot, HAlign_Center);
	DFStyleUtil::SafeSetVBoxSlotAlignment(Image->Slot, HAlign_Center);
	return RootBorder;
}

void UClickableSystemTile::Initialize(UEffectSystem* System, int Size)
{
	Label->SetText(FText::FromString(System->GetDisplayName()));
	Image->SetBrush(DFStyleUtil::SetupImageBrush(System->GetIcon(), Size));
	DFStyleUtil::TextBlockStyle(Label);
	
}

UPanelWidget* UClickableSystemTile::GetMountingPoint()
{
	return RootBorder;
}

FOnSystemPressed& UClickableSystemTile::GetOnPressed()
{
	return this->OnSystemPressed;
}

void UClickableSystemTile::Select()
{
	DFStyleUtil::RoundedBorderStyle(RootBorder, DFStyleUtil::SELECTED_LEVEL_3, 10);
}

void UClickableSystemTile::DeSelect()
{
	DFStyleUtil::RoundedBorderStyle(RootBorder, DFStyleUtil::GREY_LVL_3, 10);
}
