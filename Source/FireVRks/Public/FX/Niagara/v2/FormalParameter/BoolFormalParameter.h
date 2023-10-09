// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractFormalParameter.h"
#include "FX/Niagara/v2/ParamUtil.h"
#include "FX/Niagara/v2/ParameterValue/BoolParameterValue.h"
#include "BoolFormalParameter.generated.h"

UCLASS()
class FIREVRKS_API UBoolFormalParameter : public UAbstractFormalParameter
{
	GENERATED_BODY()
public:
	static UBoolFormalParameter* New(UObject* Outer, bool Default);

	DF_PARAMETER_GETTER(UBoolParameterValue, bool)
};
