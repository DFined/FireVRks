// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ComboBoxString.h"
#include "FX/Niagara/v2/BindingParameterValueContext.h"
#include "UI/lib/Container/DFUIContainer.h"
#include "ParamBindingSelectionWidget.generated.h"


UCLASS()
class FIREVRKS_API UParamBindingSelectionWidget : public UComboBoxString
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void ReInit(TArray<UAbstractFormalParameter*>& Options);
};
