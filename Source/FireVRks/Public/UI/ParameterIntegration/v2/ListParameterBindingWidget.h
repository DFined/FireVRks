// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParameterBindingWidget.h"
#include "Components/Border.h"
#include "FX/Niagara/v2/FormalParameter/BlockFormalParameter.h"
#include "FX/Niagara/v2/FormalParameter/ListFormalParameter.h"
#include "UI/lib/Container/DFUIStack.h"
#include "ListParameterBindingWidget.generated.h"

/**
 * 
 */
UCLASS()
class FIREVRKS_API UListParameterBindingWidget : public UParameterBindingWidget
{
	GENERATED_BODY()

	UPROPERTY()
	UBorder* OuterBorder;

	UPROPERTY()
	UDFUIStack* ListStack;

	ParameterDrawType DrawType;

public:
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override;
	virtual UPanelWidget* GetMountingPoint() override;
	UFUNCTION()
	void NewItem();
	void AddWidgetFromParam(UParameterValueContext* SubContext, UAbstractFormalParameter* ChildType);
	virtual void InitializeBindingWidget() override;
	virtual void WriteToContext(UParameterValueContext* bContext) override;
};
