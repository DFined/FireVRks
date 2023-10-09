// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Display/DisplayData.h"
#include "UI/DFUIUtil.h"
#include "UI/lib/Container/DFUIContainer.h"
#include "DisplayEditorUI.generated.h"

class ULaunchSegmentTile;

UCLASS()
class FIREVRKS_API UDisplayEditorUI : public UDFUIContainer
{
	GENERATED_BODY()

	inline static int SPACING = 15;
	inline static int BUTTON_SIZE = 32;

	UPROPERTY()
	UBorder* RootBorder;

	UPROPERTY()
	UCanvasPanel* Canvas;

	UPROPERTY()
	TArray<UWidget*> Children;

	UPROPERTY()
	TArray<UButton*> Buttons;

	UPROPERTY()
	UDisplayData* Data;

public:
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override;
	virtual UPanelWidget* GetMountingPoint() override;

	void Initialize(UDisplayData* Data);

	UFUNCTION()
	void NewSegment();
	void MakePlusButton(int Offset, int i);
	void ReTile();

	void Remove(ULaunchSegmentTile* Tile, UDisplayLaunchSegment* Segment);

	UFUNCTION(BlueprintCallable)
	static UDisplayEditorUI* NewEmpty(UPanelWidget* Parent);

	UFUNCTION(BlueprintCallable)
	static UDisplayEditorUI* New(UPanelWidget* Parent, UDisplayData* fData);
};
