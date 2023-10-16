// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractFormalParameter.h"
#include "FX/Niagara/v2/ParamUtil.h"
#include "FX/Niagara/v2/ParameterValue/ListParameterValue.h"
#include "ListFormalParameter.generated.h"

/**
 * 
 */
UCLASS()
class FIREVRKS_API UListFormalParameter : public UAbstractFormalParameter
{
	GENERATED_BODY()

	UPROPERTY()
	UAbstractFormalParameter* ChildType;

public:
	UAbstractFormalParameter* GetChildType() const
	{
		return ChildType;
	}
	
	static UListFormalParameter* New(UObject* Outer, UAbstractFormalParameter* ChildType);

	DF_PARAMETER_GETTER(UListParameterValue, TArray<UParameterValueContext*>);
};
