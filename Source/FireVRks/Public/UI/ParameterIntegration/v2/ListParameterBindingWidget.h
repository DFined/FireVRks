// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParameterBindingWidget.h"
#include "Components/Border.h"
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

public:
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override;
	virtual UPanelWidget* GetMountingPoint() override;
	virtual void Initialize(UAbstractFormalParameter* Parameter, UParameterValueContext* Context) override;
	virtual void WriteToContext(UParameterValueContext* Context) override;
};
