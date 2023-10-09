// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CoreUI/StackableLaunchInstanceTile.h"

#include "FX/Niagara/v2/MapParameterValueContext.h"
#include "UI/DFUIUtil.h"
#include "UI/Icons.h"

int UStackableLaunchInstanceTile::PLUS_BUTTON_SIZE = 32;


UPanelWidget* UStackableLaunchInstanceTile::MakeRootWidget(UWidgetTree* Tree)
{
	RootBorder = DFUIUtil::MakeWidget<UBorder>(Tree);
	DFStyleUtil::BasicBorderStyle(RootBorder, ESlateBrushDrawType::Box, DFStyleUtil::GREY_LVL_2);
	auto HBox = DFUIUtil::AddWidget<UHorizontalBox>(Tree, RootBorder);
	VBox = DFUIUtil::AddWidget<UVerticalBox>(Tree, HBox);
	
	auto DelBtn = DFUIUtil::MakeImageButton(Tree, HBox, &Icons::DELETE_ICON, PLUS_BUTTON_SIZE);
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
	UArrayLaunchParameterInputUI::Instance(VBox, Context);
	this->Parent = SegmentTile;
	
	auto PlusBtn = DFUIUtil::MakeImageButton(WidgetTree, VBox, &Icons::PLUS_ICON, PLUS_BUTTON_SIZE);
	DFStyleUtil::SafeSetVBoxSlotWidth(PlusBtn->Slot, FSlateChildSize(ESlateSizeRule::Automatic));
	PlusBtn->OnPressed.AddUniqueDynamic(this, &UStackableLaunchInstanceTile::AddTile);
}


void UStackableLaunchInstanceTile::AddTile()
{	
	Parent->NewTile(this);
}

void UStackableLaunchInstanceTile::RemoveTile()
{
	Parent->RemoveTile(this);
}
