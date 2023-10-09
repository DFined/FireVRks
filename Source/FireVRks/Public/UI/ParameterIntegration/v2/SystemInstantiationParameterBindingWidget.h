// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParameterBindingWidget.h"
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
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override;
	virtual UPanelWidget* GetMountingPoint() override;
	virtual void Initialize(UAbstractFormalParameter* fParameter, UParameterValueContext* Context) override;
	virtual void WriteToContext(UParameterValueContext* Context) override;
};
