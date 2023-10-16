// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbstractFormalParameter.h"
#include "FX/Niagara/v2/ParamUtil.h"
#include "FX/Niagara/v2/ParameterValue/ArraySelectorParameterValue.h"
#include "ArraySelectorParameter.generated.h"

UCLASS()
class FIREVRKS_API UArraySelectorParameter : public UAbstractFormalParameter
{
	GENERATED_BODY()

public:

	static UArraySelectorParameter* New(UObject* Outer);

	DF_PARAMETER_GETTER(UArraySelectorParameterValue, UGenericLauncherArray*);
};
