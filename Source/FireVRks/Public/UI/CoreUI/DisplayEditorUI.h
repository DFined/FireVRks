// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Display/DisplayData.h"
#include "DFUI/DFUI.h"
#include "DFUI/DFUIBase.h"
#include "DisplayEditorUI.generated.h"

class ULaunchSegmentTile;

UCLASS()
class FIREVRKS_API UDisplayEditorUI : public UDFUIBase
{
	GENERATED_BODY()

	inline static int SPACING = 15;
	inline static int BUTTON_SIZE = 32;

	int ReTileIn = 0;

	UPROPERTY()
	UBorder* RootBorder;

	UPROPERTY()
	UCanvasPanel* Canvas;

	UPROPERTY()
	TArray<ULaunchSegmentTile*> Children;

	UPROPERTY()
	TArray<UButton*> Buttons;

	UPROPERTY()
	UDisplayData* Data;

public:
	virtual UPanelWidget* MakeRootWidget() override;
	virtual UPanelWidget* GetMountingPoint() override;

	void InitializeDFWidget(UDisplayData* Data);

	UFUNCTION()
	void NewSegment(UWidget* InputWidget);

	UFUNCTION()
	void GetNewTime();

	void MakePlusButton(int Offset, int i);

	UFUNCTION()
	void ReTile();

	void Remove(ULaunchSegmentTile* Tile, UDisplayLaunchSegment* Segment);

	UFUNCTION(BlueprintCallable)
	static UDisplayEditorUI* NewEmpty(UPanelWidget* Parent);

	UFUNCTION(BlueprintCallable)
	static UDisplayEditorUI* New(UPanelWidget* Parent, UDisplayData* fData);

	UFUNCTION(BlueprintCallable)
	void ScheduleDisplay();

	UFUNCTION()
	void ScheduleLayout();

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
