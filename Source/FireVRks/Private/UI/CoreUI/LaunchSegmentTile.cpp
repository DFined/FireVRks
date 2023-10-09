// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\..\Public\UI\CoreUI\LaunchSegmentTile.h"

#include "FX/Niagara/v2/MapParameterValueContext.h"
#include "UI/DFUIUtil.h"
#include "UI/Icons.h"
#include "UI/CoreUI/DisplayEditorUI.h"
#include "UI/CoreUI/StackableLaunchInstanceTile.h"

UPanelWidget* ULaunchSegmentTile::MakeRootWidget(UWidgetTree* Tree)
{
	RootBorder = DFUIUtil::MakeWidget<UBorder>(Tree);
	DFStyleUtil::BasicBorderStyle(RootBorder, ESlateBrushDrawType::Box, DFStyleUtil::GREY_LVL_3);
	auto VBox = DFUIUtil::AddWidget<UVerticalBox>(Tree, RootBorder);

	auto TimeHBox = DFUIUtil::AddWidget<UHorizontalBox>(Tree, VBox);

	auto TimeLabel = DFUIUtil::AddWidget<UTextBlock>(Tree, TimeHBox);
	TimeLabel->SetText(FText::FromString("Launch Time: "));
	DFStyleUtil::TextBlockStyle(TimeLabel);
	DFStyleUtil::SafeSetHBoxSlotWidth(TimeLabel->Slot, FSlateChildSize(ESlateSizeRule::Fill));

	TimeText = DFUIUtil::AddWidget<UTextBlock>(Tree, TimeHBox);
	DFStyleUtil::TextBlockStyle(TimeText);
	DFStyleUtil::SafeSetHBoxSlotWidth(TimeText->Slot, FSlateChildSize(ESlateSizeRule::Fill));

	auto DelBtn = DFUIUtil::MakeImageButton(Tree, TimeHBox, &Icons::DELETE_ICON, 32);
	DFStyleUtil::SafeSetHBoxSlotWidth(DelBtn->Slot, FSlateChildSize(ESlateSizeRule::Automatic));
	DelBtn->OnPressed.AddUniqueDynamic(this, &ULaunchSegmentTile::Remove);


	Stack = DFUIUtil::AddUserWidget<UDFUIStack>(VBox);
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
	auto Tile = DFUIUtil::AddUserWidget<UStackableLaunchInstanceTile>(Stack);
	Tile->Initialize(Context, this);
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

	TimeText->SetText(FText::FromString(FString::SanitizeFloat(Segment->GetTime())));
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
	
	Parent->ForceLayoutPrepass();
	Parent->ReTile();
}
