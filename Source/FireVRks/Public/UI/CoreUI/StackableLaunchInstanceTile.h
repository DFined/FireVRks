// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LaunchSegmentTile.h"
#include "Components/Border.h"
#include "Components/VerticalBox.h"
#include "FX/Niagara/v2/ParameterValueContext.h"
#include "DFUI/DFUIBase.h"
#include "UI/ParameterIntegration/v2/ArrayLaunchParameterInputUI.h"
#include "StackableLaunchInstanceTile.generated.h"

/**
 * 
 */
UCLASS()
class FIREVRKS_API UStackableLaunchInstanceTile : public UDFUIBase
{
	GENERATED_BODY()

	static int PLUS_BUTTON_SIZE;
	
	UPROPERTY()
	UBorder* RootBorder;

	UPROPERTY()
	UVerticalBox* VBox;

	UPROPERTY()
	ULaunchSegmentTile* Parent;
	
	UPROPERTY()
	UParameterValueContext* Context;

	UPROPERTY()
	UArrayLaunchParameterInputUI* LaunchInputUI;

public:
	UFUNCTION()
	void AddTile();
	UFUNCTION()
	void RemoveTile();
	virtual UPanelWidget* MakeRootWidget() override;
	virtual UPanelWidget* GetMountingPoint() override;

	void Initialize(UParameterValueContext* Context, ULaunchSegmentTile* SegmentTile);

	UParameterValueContext* GetContext() const
	{
		return Context;
	}

	void ScheduleLaunch(float Delay);

};
