// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\..\Public\UI\CoreUI\LaunchSegmentTile.h"

#include "FX/Niagara/v2/MapParameterValueContext.h"
#include "UI/DFUIUtil.h"
#include "UI/Icons.h"
#include "UI/CoreUI/DisplayEditorUI.h"
#include "UI/CoreUI/StackableLaunchInstanceTile.h"
#include "Util/DFU.h"

UPanelWidget* ULaunchSegmentTile::MakeRootWidget(UWidgetTree* Tree)
{
	RootBorder = UDFUIUtil::MakeWidget<UBorder>(Tree);
	DFStyleUtil::BasicBorderStyle(RootBorder, ESlateBrushDrawType::Box, DFStyleUtil::GREY_LVL_3);
	auto VBox = UDFUIUtil::AddWidget<UVerticalBox>(Tree, RootBorder);

	auto TimeHBox = UDFUIUtil::AddWidget<UHorizontalBox>(Tree, VBox);

	auto TimeLabel = UDFUIUtil::AddWidget<UTextBlock>(Tree, TimeHBox);
	TimeLabel->SetText(FText::FromString("Launch Time: "));
	DFStyleUtil::TextBlockStyle(TimeLabel);
	DFStyleUtil::SafeSetHBoxSlotWidth(TimeLabel->Slot, FSlateChildSize(ESlateSizeRule::Fill));

	TimeText = UDFUIUtil::AddWidget<UTextBlock>(Tree, TimeHBox);
	DFStyleUtil::TextBlockStyle(TimeText);
	DFStyleUtil::SafeSetHBoxSlotWidth(TimeText->Slot, FSlateChildSize(ESlateSizeRule::Fill));

	auto DelBtn = UDFUIUtil::MakeImageButton(Tree, TimeHBox, &Icons::DELETE_ICON, 32);
	DFStyleUtil::SafeSetHBoxSlotWidth(DelBtn->Slot, FSlateChildSize(ESlateSizeRule::Automatic));
	DelBtn->OnPressed.AddUniqueDynamic(this, &ULaunchSegmentTile::Remove);


	Stack = UDFUIUtil::AddUserWidget<UDFUIStack>(VBox);
	return RootBorder;
}

UPanelWidget* ULaunchSegmentTile::GetMountingPoint()
{
	return Stack->GetMountingPoint();
}

UPanelSlot* ULaunchSegmentTile::Append(UWidget* Widget)
{
	return Stack->Append(Widget);
}

void ULaunchSegmentTile::NewTile(UParameterValueContext* Context)
{
	auto Tile = UDFUIUtil::AddUserWidget<UStackableLaunchInstanceTile>(Stack);
	Tile->Initialize(Context, this);
	Tile->GetLayoutChangeDelegate()->AddUniqueDynamic(this, &ULaunchSegmentTile::LayoutChanged);
	Tiles.Add(Tile);
}

void ULaunchSegmentTile::NewTile(UWidget* Widget)
{
	int Num = this->GetMountingPoint()->GetAllChildren().Find(Widget) + 1;
	auto Context = UMapParameterValueContext::New(Segment);
	Segment->GetLaunchSettings()->Insert(Context, Num);
	NewTile(Context);
	
	Parent->ForceLayoutPrepass();
	Parent->ReTile();
}

void ULaunchSegmentTile::Initialize(UDisplayLaunchSegment* fSegment, UDisplayEditorUI* EditorParent)
{
	this->Segment = fSegment;
	for (auto Context : *Segment->GetLaunchSettings())
	{
		NewTile(Context);
	}

	TimeText->SetText(FText::FromString(DFU::SecondsToTimeCode(Segment->GetTime())));
	this->Parent = EditorParent;
}

void ULaunchSegmentTile::Remove()
{
	Parent->Remove(this, this->Segment);
}

void ULaunchSegmentTile::RemoveTile(UStackableLaunchInstanceTile* StackableLaunchInstanceTile)
{
	this->GetMountingPoint()->GetAllChildren().Remove(StackableLaunchInstanceTile);
	this->Segment->GetLaunchSettings()->Remove(StackableLaunchInstanceTile->GetContext());
	StackableLaunchInstanceTile->RemoveFromParent();

	if(Segment->GetLaunchSettings()->Num() == 0)
	{
		Remove();
	}
	
	Parent->ForceLayoutPrepass();
	Parent->ReTile();
	Tiles.Remove(StackableLaunchInstanceTile);
}

void ULaunchSegmentTile::ScheduleLaunch()
{
	for (auto Tile : Tiles)
	{
		Tile->ScheduleLaunch(Segment->GetTime());
	}
}
