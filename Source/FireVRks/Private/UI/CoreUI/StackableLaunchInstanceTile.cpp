// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CoreUI/StackableLaunchInstanceTile.h"

#include "DFUI/DFUI.h"
#include "UI/Icons.h"
#include "Util/DFStatics.h"

int UStackableLaunchInstanceTile::PLUS_BUTTON_SIZE = 32;


UPanelWidget* UStackableLaunchInstanceTile::MakeRootWidget()
{
	RootBorder = DFUI::MakeWidget<UBorder>(this);
	DFStyleUtil::BasicBorderStyle(RootBorder, DFStyleUtil::GREY_LVL_2);
	auto HBox = DFUI::AddWidget<UHorizontalBox>(RootBorder);
	VBox = DFUI::AddWidget<UVerticalBox>(HBox);
	
	auto DelBtn = DFUI::AddImageButton(HBox, UDFStatics::ICONS->DELETE_ICON, PLUS_BUTTON_SIZE);
	DFStyleUtil::SafeSetHBoxSlotWidth(DelBtn->Slot, FSlateChildSize(ESlateSizeRule::Automatic));
	DelBtn->OnPressed.AddUniqueDynamic(this, &UStackableLaunchInstanceTile::RemoveTile);
	
	return RootBorder;
}

UPanelWidget* UStackableLaunchInstanceTile::GetMountingPoint()
{
	return VBox;
}

void UStackableLaunchInstanceTile::Initialize(UParameterValueContext* bContext, ULaunchSegmentTile* SegmentTile)
{
	this->Context = bContext; 
	LaunchInputUI = UArrayLaunchParameterInputUI::Instance(VBox, Context);
	LaunchInputUI->GetLayoutChangeDelegate()->AddUniqueDynamic(this, &UStackableLaunchInstanceTile::LayoutChanged);
	this->Parent = SegmentTile;
	
	auto PlusBtn = DFUI::AddImageButton(VBox, UDFStatics::ICONS->PLUS_ICON, PLUS_BUTTON_SIZE);
	DFStyleUtil::SafeSetVBoxSlotWidth(PlusBtn->Slot, FSlateChildSize(ESlateSizeRule::Automatic));
	PlusBtn->OnPressed.AddUniqueDynamic(this, &UStackableLaunchInstanceTile::AddTile);
}

void UStackableLaunchInstanceTile::ScheduleLaunch(float Delay)
{
	LaunchInputUI->Launch(Delay, false);
}


void UStackableLaunchInstanceTile::AddTile()
{	
	Parent->NewTile(this);
}

void UStackableLaunchInstanceTile::RemoveTile()
{
	Parent->RemoveTile(this);
}
