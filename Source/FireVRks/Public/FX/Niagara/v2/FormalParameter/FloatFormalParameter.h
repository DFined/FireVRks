// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractFormalParameter.h"
#include "FX/Niagara/v2/ParamUtil.h"
#include "FX/Niagara/v2/ParameterValue/FloatParameterValue.h"
#include "FloatFormalParameter.generated.h"

UCLASS()
class FIREVRKS_API UFloatFormalParameter : public UAbstractFormalParameter
{
	GENERATED_BODY()

public:
	static UFloatFormalParameter* New(UObject* Outer, float Default);	

	DF_PARAMETER_GETTER(UFloatParameterValue, float);
};
