// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractFormalParameter.h"
#include "FX/Niagara/v2/ParamUtil.h"
#include "FX/Niagara/v2/ParameterValue/EnumParameterValue.h"
#include "EnumFormalParameter.generated.h"

/**
 * 
 */
UCLASS()
class FIREVRKS_API UEnumFormalParameter : public UAbstractFormalParameter
{
	GENERATED_BODY()

	EnumLike* ValueType;

public:
	static UEnumFormalParameter* New(UObject* Outer, EnumLikeValue* DefaultVal);

	DF_PARAMETER_GETTER(UEnumParameterValue, EnumLikeValue*)
};
