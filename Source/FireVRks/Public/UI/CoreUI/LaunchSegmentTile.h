// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Display/DisplayLaunchSegment.h"
#include "UI/CoreUI/DisplayEditorUI.h"
#include "DFUI/DFUI.h"
#include "DFUI/DFUIBase.h"
#include "UI/lib/Container/DFUIStack.h"
#include "UI/lib/ValidatedTextBox/TimeValidatedTextBox.h"
#include "UI/ParameterIntegration/v2/ParameterBindingWidget.h"
#include "LaunchSegmentTile.generated.h"

class UStackableLaunchInstanceTile;
/**
 * 
 */
UCLASS()
class FIREVRKS_API ULaunchSegmentTile : public UDFUIBase
{
	GENERATED_BODY()

	UPROPERTY()
	UBorder* RootBorder;

	UPROPERTY()
	UDFUIStack* Stack;

	UPROPERTY()
	UTimeValidatedTextBox* TimeText;

	UPROPERTY()
	UDisplayLaunchSegment* Segment;

	UPROPERTY()
	UDisplayEditorUI* Parent;

	UPROPERTY()
	TArray<UStackableLaunchInstanceTile*> Tiles;


	FOnDFUILayoutChange LayoutChangedDelegate;

public:
	UFUNCTION()
	void OnTimeChanged(float NewTime);
	virtual UPanelWidget* MakeRootWidget() override;
	virtual UPanelWidget* GetMountingPoint() override;

	virtual UPanelSlot* Append(UWidget* Widget) override;
	void NewTile(UParameterValueContext* Context);
	void NewTile(UWidget* Widget);

	void Initialize(UDisplayLaunchSegment* fSegment, UDisplayEditorUI* EditorParent);

	UFUNCTION()
	void Remove();
	void RemoveTile(UStackableLaunchInstanceTile* StackableLaunchInstanceTile);

	void ScheduleLaunch();
};
