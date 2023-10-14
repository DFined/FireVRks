// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Display/DisplayLaunchSegment.h"
#include "UI/CoreUI/DisplayEditorUI.h"
#include "UI/DFUIUtil.h"
#include "UI/lib/Container/DFUIContainer.h"
#include "UI/lib/Container/DFUIStack.h"
#include "LaunchSegmentTile.generated.h"

class UStackableLaunchInstanceTile;
/**
 * 
 */
UCLASS()
class FIREVRKS_API ULaunchSegmentTile : public UDFUIContainer
{
	GENERATED_BODY()
	
	UPROPERTY()
	UBorder* RootBorder;

	UPROPERTY()
	UDFUIStack* Stack;

	UPROPERTY()
	UTextBlock* TimeText;

	UPROPERTY()
	UDisplayLaunchSegment* Segment;
	
	UPROPERTY()
	UDisplayEditorUI* Parent;

public:
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override;
	virtual UPanelWidget* GetMountingPoint() override;

	virtual UPanelSlot* Append(UWidget* Widget) override;
	void NewTile(UParameterValueContext* Context);
	void NewTile(UWidget* Widget);

	void Initialize(UDisplayLaunchSegment* fSegment, UDisplayEditorUI* EditorParent);
	
	UFUNCTION()
	void Remove();
	void RemoveTile(UStackableLaunchInstanceTile* StackableLaunchInstanceTile);
};
