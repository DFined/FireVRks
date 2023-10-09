// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CoreUI/DisplayEditorUI.h"

#include "Components/ScrollBoxSlot.h"
#include "UI/DFUIUtil.h"
#include "UI/Icons.h"
#include "UI/CoreUI/LaunchSegmentTile.h"

UPanelWidget* UDisplayEditorUI::MakeRootWidget(UWidgetTree* Tree)
{
	RootBorder = DFUIUtil::MakeWidget<UBorder>(Tree);
	DFStyleUtil::BasicBorderStyle(RootBorder, ESlateBrushDrawType::Box, DFStyleUtil::GREY_LVL_2);

	Canvas = DFUIUtil::AddWidget<UCanvasPanel>(Tree, RootBorder);

	return RootBorder;
}


UPanelWidget* UDisplayEditorUI::GetMountingPoint()
{
	return Canvas;
}

void UDisplayEditorUI::Initialize(UDisplayData* fData)
{
	this->Data = fData;
	if (auto bSlot = Cast<UScrollBoxSlot>(this->Slot))
	{
		bSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
	}
	for (auto Segment : *Data->GetLaunchSegments())
	{
		auto SegmentUI = DFUIUtil::AddUserWidget<ULaunchSegmentTile>(Canvas);
		auto bSlot = Cast<UCanvasPanelSlot>(SegmentUI->Slot);
		SegmentUI->Initialize(Segment, this);
		bSlot->SetAutoSize(true);
		Children.Add(SegmentUI);
	}
	Canvas->ForceLayoutPrepass();
	this->ReTile();
}

void UDisplayEditorUI::NewSegment()
{

	auto Segment = UDisplayLaunchSegment::New(Data);
	Data->GetLaunchSegments()->Add(Segment);
	
	auto SegmentUI = DFUIUtil::AddUserWidget<ULaunchSegmentTile>(Canvas);
	auto bSlot = Cast<UCanvasPanelSlot>(SegmentUI->Slot);
	SegmentUI->Initialize(Segment, this);
	bSlot->SetAutoSize(true);
	Children.Add(SegmentUI);

	Canvas->ForceLayoutPrepass();
	ReTile();
}

void UDisplayEditorUI::MakePlusButton(int Offset, int i)
{
	auto Btn = DFUIUtil::MakeImageButton(WidgetTree, Canvas, &Icons::PLUS_ICON, BUTTON_SIZE);
	Buttons.Add(Btn);
	if (auto bSlot = Cast<UCanvasPanelSlot>(Btn->Slot))
	{
		bSlot->SetPosition(FVector2D(Offset + (2 * SPACING + BUTTON_SIZE)*i + SPACING, BUTTON_SIZE));
		bSlot->SetAutoSize(true);
	}
	Btn->OnPressed.AddUniqueDynamic(this, &UDisplayEditorUI::NewSegment);
}

void UDisplayEditorUI::ReTile()
{
	for (UButton* Button : Buttons)
	{
		Canvas->RemoveChild(Button);
		Button->RemoveFromParent();
	}
	Buttons.Empty();

	auto Offset = 0;
	for (int i = 0; i < Children.Num(); ++i)
	{
		auto Widget = Children[i];
		if (auto bSlot = Cast<UCanvasPanelSlot>(Widget->Slot))
		{
			bSlot->SetPosition(FVector2D(Offset + (2 * SPACING + BUTTON_SIZE) * i, 0));
			Offset += Widget->GetDesiredSize().X;
		}

		MakePlusButton(Offset, i);
	}
	MakePlusButton(SPACING, 0);
}

void UDisplayEditorUI::Remove(ULaunchSegmentTile* Tile, UDisplayLaunchSegment* Segment)
{
	Data->Remove(Segment);
	Children.Remove(Tile);
	Tile->RemoveFromParent();
	ReTile();
}

UDisplayEditorUI* UDisplayEditorUI::NewEmpty(UPanelWidget* Parent)
{
	auto Editor = DFUIUtil::AddUserWidget<UDisplayEditorUI>(Parent);
	Editor->Initialize(UDisplayData::New(Editor));
	return Editor;
}

UDisplayEditorUI* UDisplayEditorUI::New(UPanelWidget* Parent, UDisplayData* Data)
{
	auto Editor = DFUIUtil::AddUserWidget<UDisplayEditorUI>(Parent);
	Editor->Initialize(Data);
	return Editor;
}
