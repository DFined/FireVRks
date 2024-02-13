// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ParameterIntegration/v2/ClickableSystemTile.h"

#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "DFUI/DFUI.h"

void UClickableSystemTile::OnClick()
{
	OnSystemPressed.Broadcast(this);
}

UPanelWidget* UClickableSystemTile::MakeRootWidget()
{
	RootBorder = DFUI::MakeWidget<UBorder>(this);
	DFStyleUtil::RoundedBorderStyle(RootBorder, DFStyleUtil::GREY_LVL_3, 10);

	Button = DFUI::AddWidget<UButton>(RootBorder);
	Button->OnPressed.AddUniqueDynamic(this, &UClickableSystemTile::OnClick);
	DFStyleUtil::TextButtonStyle(Button, DFStyleUtil::GREY_LVL_3);
	
	auto Box = DFUI::MakeWidget<UVerticalBox>(this);
	Button->SetContent(Box);
	

	Image = DFUI::AddWidget<UImage>(Box);
	Label = DFUI::AddWidget<UTextBlock>(Box);
	DFStyleUtil::SafeSetVBoxSlotAlignment(Label->Slot, HAlign_Center);
	DFStyleUtil::SafeSetVBoxSlotAlignment(Image->Slot, HAlign_Center);
	return RootBorder;
}

void UClickableSystemTile::Initialize(UEffectSystem* System, int Size)
{
	Label->SetText(FText::FromString(System->GetDisplayName()));
	Image->SetBrush(DFStyleUtil::SetupImageBrush(DFStyleUtil::LoadCachedTexture(System->GetIcon()), Size));
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
