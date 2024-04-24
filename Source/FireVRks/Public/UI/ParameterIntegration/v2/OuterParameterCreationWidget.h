// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParameterBindingWidget.h"
#include "ParameterControlWidget.h"
#include "Components/Border.h"
#include "DFUI/Upgrade/DFVBoxEx.h"
#include "FX/Niagara/v2/System/CustomEffectSystem.h"
#include "OuterParameterCreationWidget.generated.h"

/**
 * 
 */
UCLASS()
class FIREVRKS_API UOuterParameterCreationWidget : public UParameterControlWidget
{
	GENERATED_BODY()

	UPROPERTY()
	UBorder* RootBorder;

	UPROPERTY()
	UDFVBoxEx* Box;

	UPROPERTY()
	UCustomEffectSystem* System;

public:
	UFUNCTION()
	void NewParameter(UWidget* Widget);
	UFUNCTION()
	void OnAddParameter();
	void Draw();

	virtual UPanelWidget* MakeRootWidget() override;
	virtual UPanelWidget* GetMountingPoint() override;

	void SetSystem(UCustomEffectSystem* bSystem);

	UFUNCTION()
	void MoveUp(UParameterBindingWidget* Widget);

	UFUNCTION()
	void MoveDown(UParameterBindingWidget* Widget);
};
