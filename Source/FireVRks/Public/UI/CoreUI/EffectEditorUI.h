// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HorizontalBox.h"
#include "FX/Niagara/v2/BindingParameterValueContext.h"
#include "UI/lib/Container/DFUIContainer.h"
#include "EffectEditorUI.generated.h"

/**
 * 
 */
UCLASS()
class FIREVRKS_API UEffectEditorUI : public UDFUIContainer
{
	GENERATED_BODY()

	UPROPERTY()
	UHorizontalBox* RootHBox;
	
	UPROPERTY()
	UBindingParameterValueContext* Context;

public:
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override;
	virtual UPanelWidget* GetMountingPoint() override;

	UFUNCTION(BlueprintCallable)
	static UEffectEditorUI* EmptyInstance(UPanelWidget* Parent);
};
