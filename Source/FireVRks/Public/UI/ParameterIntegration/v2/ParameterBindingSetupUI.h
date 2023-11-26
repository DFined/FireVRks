// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SystemDisplayTile.h"
#include "Components/Border.h"
#include "Components/VerticalBox.h"
#include "FX/Niagara/v2/BindingParameterValueContext.h"
#include "FX/Niagara/v2/System/EffectSystem.h"
#include "UI/lib/Container/DFUIContainer.h"
#include "Util/DFId.h"
#include "ParameterBindingSetupUI.generated.h"

/**
 * 
 */
UCLASS()
class FIREVRKS_API UParameterBindingSetupUI : public UDFUIContainer
{
	GENERATED_BODY()

	UPROPERTY()
	UBorder* RootBorder;

	UPROPERTY()
	UDFId* SystemId = nullptr;

	UPROPERTY()
	UEffectSystem* System;
	
	UPROPERTY()
	USystemDisplayTile* SystemDisplayTile;
	
	UPROPERTY()
	UVerticalBox* ParamsBox;

public:
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override;
	void Setup(UParameterValueContext* Context);
	void SetSystem(UEffectSystem* bSystem);
	virtual UPanelWidget* GetMountingPoint() override;

	UFUNCTION(BlueprintCallable)
	static UParameterBindingSetupUI* InstanceFrom(UPanelWidget* Parent, UBindingParameterValueContext* Context);
};
