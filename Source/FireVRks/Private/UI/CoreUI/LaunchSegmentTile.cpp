// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\..\Public\UI\CoreUI\LaunchSegmentTile.h"

#include "FX/Niagara/v2/MapParameterValueContext.h"
#include "DFUI/DFUI.h"
#include "UI/Icons.h"
#include "UI/CoreUI/DisplayEditorUI.h"
#include "UI/CoreUI/StackableLaunchInstanceTile.h"
#include "Util/DFStatics.h"
#include "Util/DFU.h"

void ULaunchSegmentTile::OnTimeChanged(float NewTime)
{
	this->Segment->SetTime(NewTime);
}

UPanelWidget* ULaunchSegmentTile::MakeRootWidget()
{
	RootBorder = DFUI::MakeWidget<UBorder>(this);
	DFStyleUtil::BasicBorderStyle(RootBorder, DFStyleUtil::GREY_LVL_3);
	auto VBox = DFUI::AddWidget<UVerticalBox>(RootBorder);

	auto TimeHBox = DFUI::AddWidget<UHorizontalBox>(VBox);

	auto TimeLabel = DFUI::AddWidget<UTextBlock>(TimeHBox);
	TimeLabel->SetText(FText::FromString("Launch Time: "));
	DFStyleUtil::TextBlockStyle(TimeLabel);
	DFStyleUtil::SafeSetHBoxSlotWidth(TimeLabel->Slot, FSlateChildSize(ESlateSizeRule::Fill), HAlign_Fill, VAlign_Center);

	TimeText = DFUI::AddWidget<UTimeValidatedTextBox>(TimeHBox);
	TimeText->GetOnTimeChanged().AddUniqueDynamic(this, &ULaunchSegmentTile::OnTimeChanged);
	DFStyleUtil::SafeSetHBoxSlotWidth(TimeText->Slot, FSlateChildSize(ESlateSizeRule::Fill), HAlign_Fill, VAlign_Center);

	auto DelBtn = DFUI::AddImageButton(TimeHBox, UDFStatics::ICONS->DELETE_ICON, 32);
	DFStyleUtil::SafeSetHBoxSlotWidth(DelBtn->Slot, FSlateChildSize(ESlateSizeRule::Automatic));
	DelBtn->OnPressed.AddUniqueDynamic(this, &ULaunchSegmentTile::Remove);


	Stack = DFUI::AddWidget<UDFUIStack>(VBox);
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
	auto Tile = DFUI::AddWidget<UStackableLaunchInstanceTile>(Stack);
	Tile->Initialize(Context, this);
	Tile->GetLayoutChangeDelegate()->AddUniqueDynamic(this, &ULaunchSegmentTile::LayoutChanged);
	Tiles.Add(Tile);
}

void ULaunchSegmentTile::NewTile(UWidget* Widget)
{
	int Num = this->GetMountingPoint()->GetAllChildren().Find(Widget) + 1;
	auto Context = UMapParameterValueContext::Instance(Segment);
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

	TimeText->SetValue(DFU::SecondsToTimeCode(Segment->GetTime()));
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

