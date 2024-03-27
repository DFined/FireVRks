// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ComboBoxString.h"
#include "FX/Niagara/v2/FormalParameter/AbstractFormalParameter.h"
#include "ParamBindingSelectionWidget.generated.h"


UCLASS()
class FIREVRKS_API UParamBindingSelectionWidget : public UComboBoxString
{
	GENERATED_BODY()
	UPROPERTY()
	TArray<UAbstractFormalParameter*> Parameters = TArray<UAbstractFormalParameter*>();

public:
	void AddOptionParam(UAbstractFormalParameter* Parameter);

	UAbstractFormalParameter* GetSelectedParam();

	void SetSelectedParam(UAbstractFormalParameter* Parameter);

	bool RemoveOptionParam(UAbstractFormalParameter* Parameter);

	UFUNCTION()
	void ReInit(TArray<UAbstractFormalParameter*>& Options);
	void RenameOptionParam(UAbstractFormalParameter* Param);
};
