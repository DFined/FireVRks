// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HorizontalBox.h"
#include "FX/Niagara/v2/ParameterValueContext.h"
#include "FX/Niagara/v2/System/CustomEffectSystem.h"
#include "UI/lib/Container/DFUIContainer.h"
#include "UI/ParameterIntegration/v2/ParameterBindingSetupUI.h"
#include "EffectEditorUI.generated.h"

UCLASS(BlueprintType, Blueprintable)
class FIREVRKS_API UEffectEditorUI : public UDFUIContainer
{
	GENERATED_BODY()

	UPROPERTY()
	UHorizontalBox* RootHBox;
	
	UPROPERTY()
	UParameterValueContext* DefaultValueContext;

	UPROPERTY()
	UCustomEffectSystem* System;
	
	UPROPERTY()
	UVerticalBox* SubsystemsVBox;

public:
	UFUNCTION()
	void OnNewSystem();
	
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override;
	virtual UPanelWidget* GetMountingPoint() override;

	void Init();
	void MoveSystemUp(UParameterBindingSetupUI* ParameterBindingSetupUI);
	void MoveSystemDown(UParameterBindingSetupUI* ParameterBindingSetupUI);

	UFUNCTION(BlueprintCallable)
	static UEffectEditorUI* EmptyInstance(UPanelWidget* Parent);

	UFUNCTION(BlueprintCallable)
	UCustomEffectSystem* GetSystem() const;

	void SetSystem(UCustomEffectSystem* bSystem);
};
