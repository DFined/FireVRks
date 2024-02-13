// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HorizontalBox.h"
#include "Components/WidgetSwitcher.h"
#include "FX/Niagara/v2/ParameterValueContext.h"
#include "FX/Niagara/v2/System/CustomEffectSystem.h"
#include "DFUI/DFUIBase.h"
#include "UI/ParameterIntegration/v2/EffectSystemSavingWidget.h"
#include "UI/ParameterIntegration/v2/ParameterBindingSetupUI.h"
#include "EffectEditorUI.generated.h"

UCLASS(BlueprintType, Blueprintable)
class FIREVRKS_API UEffectEditorUI : public UDFUIBase
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

	UPROPERTY()
	UButton* LoadButton;
	
	UPROPERTY()
	UButton* SaveButton;
	
	UPROPERTY()
	UButton* SaveAsButton;

	UPROPERTY()
	UWidgetSwitcher* Switcher;

	UPROPERTY()
	UEffectSystemSavingWidget* SavingWidget;

	UPROPERTY()
	UImage* Viewport;

	UPROPERTY()
	UTextureRenderTarget2D* MaterialInterface;

public:
	UFUNCTION()
	void OnNewSystem();
	
	virtual UPanelWidget* MakeRootWidget() override;
	virtual UPanelWidget* GetMountingPoint() override;

	void Init(UTextureRenderTarget2D* Material);
	void MoveSystemUp(UParameterBindingSetupUI* ParameterBindingSetupUI);
	void MoveSystemDown(UParameterBindingSetupUI* ParameterBindingSetupUI);

	UFUNCTION(BlueprintCallable)
	static UEffectEditorUI* Instance(UPanelWidget* Parent, UTextureRenderTarget2D* MaterialForViewport);

	UFUNCTION(BlueprintCallable)
	UCustomEffectSystem* GetSystem() const;

	UFUNCTION()
	void SaveAs();
	
	UFUNCTION(BlueprintCallable)
	void BuildToolbar(UHorizontalBox* Parent);

	void SetSystem(UCustomEffectSystem* bSystem);
};
