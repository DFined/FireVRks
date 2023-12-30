// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableTextBox.h"
#include "Components/VerticalBox.h"
#include "FX/Niagara/v2/FormalParameter/ParameterType.h"
#include "UI/lib/Container/DFUIContainer.h"
#include "ParameterCreatorInput.generated.h"

UCLASS()
class FIREVRKS_API UParameterCreatorInput : public UDFUIContainer
{
	GENERATED_BODY()
	
	UPROPERTY()
	UVerticalBox* RootBox;
	
	UPROPERTY()
	UEditableTextBox* ParamNameInput;
	
	UPROPERTY()
	UComboBoxString* ParamTypeInput;
	
	UPROPERTY()
	UCheckBox* ParamRequiredInput;

public:
	inline static constexpr ParameterType INSTANTIABLE_TYPES[] = {INTEGER, FLOAT, COLOR, BOOLEAN};
	
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override;
	virtual UPanelWidget* GetMountingPoint() override;

	FString GetParamName();
	ParameterType GetType();
	bool GetRequired();
};
