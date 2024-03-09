// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectParameterInputUI.h"
#include "ParameterBindingWidget.h"
#include "Components/Border.h"
#include "FX/Niagara/v2/ParameterValue/SystemInstantiationParameterValue.h"
#include "SystemInstantiationParameterBindingWidget.generated.h"

UCLASS()
class FIREVRKS_API USystemInstantiationParameterBindingWidget : public UParameterBindingWidget
{
	GENERATED_BODY()
	
	UPROPERTY()
	UEffectSystem* System;
	
	UPROPERTY()
	UBorder* OuterBorder;

	UPROPERTY()
	UEffectParameterInputUI* InstanceParamUI;

public:
	virtual UPanelWidget* MakeRootWidget() override;
	virtual UPanelWidget* GetMountingPoint() override;
	UFUNCTION()
	void SetupSystem(UEffectSystem* bSystem);
	virtual void InitializeBindingWidget() override;
	virtual void WriteToContext(UParameterValueContext* Context) override;
};
