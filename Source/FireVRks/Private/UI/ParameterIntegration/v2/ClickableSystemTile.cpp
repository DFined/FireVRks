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
	EffectSystem = System;
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

UEffectSystem*& UClickableSystemTile::GetEffectSystem()
{
	return EffectSystem;
}

void UClickableSystemTile::Select()
{
	Button->WidgetStyle.Normal.TintColor = FLinearColor(0.1,0.3,0.7,0.4);
	Button->WidgetStyle.Hovered.TintColor = FLinearColor(0.1,0.3,0.7,0.4);
	DFStyleUtil::RoundedBorderStyle(RootBorder, DFStyleUtil::SELECTED_LEVEL_3, 10);
}

void UClickableSystemTile::DeSelect()
{
	Button->WidgetStyle.Normal.TintColor = FLinearColor(0,0,0,0);
	Button->WidgetStyle.Hovered.TintColor = FLinearColor(0,0,0,0);
	DFStyleUtil::RoundedBorderStyle(RootBorder, DFStyleUtil::GREY_LVL_3, 10);
}
