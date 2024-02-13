// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CoreUI/DisplayEditorUI.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/ScrollBoxSlot.h"
#include "Kismet/GameplayStatics.h"
#include "DFUI/DFUI.h"
#include "UI/EDFUI.h"
#include "UI/Icons.h"
#include "UI/CoreUI/LaunchSegmentTile.h"
#include "UI/lib/ValidatedTextBox/TimeValidatedTextBox.h"
#include "Util/DFStatics.h"

UPanelWidget* UDisplayEditorUI::MakeRootWidget()
{
	RootBorder = DFUI::MakeWidget<UBorder>(this);
	DFStyleUtil::BasicBorderStyle(RootBorder, DFStyleUtil::GREY_LVL_2);

	Canvas = DFUI::AddWidget<UCanvasPanel>(RootBorder);

	return RootBorder;
}


UPanelWidget* UDisplayEditorUI::GetMountingPoint()
{
	return Canvas;
}

void UDisplayEditorUI::InitializeDFWidget(UDisplayData* fData)
{
	this->Data = fData;
	if (auto bSlot = Cast<UScrollBoxSlot>(this->Slot))
	{
		bSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
	}
	for (auto Segment : *Data->GetLaunchSegments())
	{
		auto SegmentUI = DFUI::AddWidget<ULaunchSegmentTile>(Canvas);
		auto bSlot = Cast<UCanvasPanelSlot>(SegmentUI->Slot);
		SegmentUI->Initialize(Segment, this);
		bSlot->SetAutoSize(true);
		Children.Add(SegmentUI);
		SegmentUI->GetLayoutChangeDelegate()->AddUniqueDynamic(this, &UDisplayEditorUI::ScheduleLayout);
	}
	this->ReTile();
}

void UDisplayEditorUI::NewSegment(UWidget* Input)
{
	auto TimeBox = Cast<UTimeValidatedTextBox>(Input);

	auto Segment = UDisplayLaunchSegment::New(Data);
	Data->GetLaunchSegments()->Add(Segment);
	Segment->SetTime(TimeBox->GetSeconds());

	auto SegmentUI = DFUI::AddWidget<ULaunchSegmentTile>(Canvas);
	auto bSlot = Cast<UCanvasPanelSlot>(SegmentUI->Slot);
	SegmentUI->Initialize(Segment, this);
	bSlot->SetAutoSize(true);
	Children.Add(SegmentUI);

	SegmentUI->GetLayoutChangeDelegate()->AddUniqueDynamic(this, &UDisplayEditorUI::ScheduleLayout);
	ReTile();
}

void UDisplayEditorUI::GetNewTime()
{
	auto Ctrlr = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	auto Popup = EDFUI::OpenInputPopup<UTimeValidatedTextBox>(Ctrlr, "Enter launch time for new segment");
	auto InputBox = Popup->GetWidget<UTimeValidatedTextBox>();
	InputBox->SetSeconds(0);
	Popup->GetOnConfirm()->AddUniqueDynamic(this, &UDisplayEditorUI::NewSegment);
}

void UDisplayEditorUI::MakePlusButton(int Offset, int i)
{
	auto Btn = DFUI::AddImageButton(Canvas, UDFStatics::ICONS->PLUS_ICON, BUTTON_SIZE);
	Buttons.Add(Btn);
	if (auto bSlot = Cast<UCanvasPanelSlot>(Btn->Slot))
	{
		bSlot->SetPosition(FVector2D(Offset + (2 * SPACING + BUTTON_SIZE) * i + SPACING, BUTTON_SIZE));
		bSlot->SetAutoSize(true);
	}
	Btn->OnPressed.AddUniqueDynamic(this, &UDisplayEditorUI::GetNewTime);
}

void UDisplayEditorUI::ReTile()
{
	ForceLayoutPrepass();
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
	auto Editor = DFUI::AddWidget<UDisplayEditorUI>(Parent);
	Editor->InitializeDFWidget(UDisplayData::New(Editor));
	return Editor;
}

UDisplayEditorUI* UDisplayEditorUI::New(UPanelWidget* Parent, UDisplayData* Data)
{
	auto Editor = DFUI::AddWidget<UDisplayEditorUI>(Parent);
	Editor->InitializeDFWidget(Data);
	return Editor;
}

void UDisplayEditorUI::ScheduleDisplay()
{
	auto Segments = Data->GetLaunchSegments();

	for(int i = 0; i < Segments->Num(); i++)
	{
		auto LaunchSettings = *(*Segments)[i]->GetLaunchSettings();
		Children[i]->ScheduleLaunch();
	}
}

void UDisplayEditorUI::ScheduleLayout()
{
		ReTileIn = 20;
}

void UDisplayEditorUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if(ReTileIn == 0)
	{
		ReTile();
		ReTileIn--;
	}
	else 
	{
		ReTileIn--;
	}	
}
