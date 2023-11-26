// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParameterControlWidget.h"
#include "Components/Border.h"
#include "Components/VerticalBox.h"
#include "FX/Niagara/v2/BindingParameterValueContext.h"
#include "FX/Niagara/v2/FormalParameter/AbstractFormalParameter.h"
#include "UI/lib/Container/DFUIContainer.h"
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
	UVerticalBox* Box;

	UPROPERTY()
	UBindingParameterValueContext* Context;
	
public:
	UFUNCTION()
	void NewParameter(UWidget* Widget);
	UFUNCTION()
	void OnAddParameter();
	void Draw(UBindingParameterValueContext* ContextIn);

	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override;
	virtual UPanelWidget* GetMountingPoint() override;
};
