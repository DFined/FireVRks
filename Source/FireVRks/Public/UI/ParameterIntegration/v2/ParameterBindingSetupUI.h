// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SystemDisplayTile.h"
#include "Components/Border.h"
#include "Components/HorizontalBox.h"
#include "Components/VerticalBox.h"
#include "DFUI/DFUIBase.h"
#include "ParameterBindingSetupUI.generated.h"

UCLASS()
class FIREVRKS_API UParameterBindingSetupUI : public UDFUIBase
{
	GENERATED_BODY()

	UPROPERTY()
	UBorder* RootBorder;
	
	UPROPERTY()
	USystemDisplayTile* SystemDisplayTile;
	
	UPROPERTY()
	UVerticalBox* ParamsBox;

	UPROPERTY()
	UEffectSystem* System;

	UPROPERTY()
	USubsystemConfig* SubsystemConfig;

	UPROPERTY()
	UHorizontalBox* HeaderBox;

public:
	UFUNCTION()
	void Delete();
	
	virtual UPanelWidget* MakeRootWidget() override;
	
	UFUNCTION()
	void MoveUp();
	
	UFUNCTION()
	void MoveDown();

	UFUNCTION()
	void Setup(UEffectSystem* bSystem);
	void SetSystem(UEffectSystem* bSystem);
	virtual UPanelWidget* GetMountingPoint() override;

	UFUNCTION(BlueprintCallable)
	static UParameterBindingSetupUI* InstanceFrom(UPanelWidget* bParent, UEffectSystem* bSystem, USubsystemConfig* bBindings);	
};
