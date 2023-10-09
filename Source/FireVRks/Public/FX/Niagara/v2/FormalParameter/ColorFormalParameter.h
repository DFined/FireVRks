// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractFormalParameter.h"
#include "FX/Niagara/v2/ParamUtil.h"
#include "FX/Niagara/v2/ParameterValue/ColorParameterValue.h"
#include "ColorFormalParameter.generated.h"

/**
 * 
 */
UCLASS()
class FIREVRKS_API UColorFormalParameter : public UAbstractFormalParameter
{
	GENERATED_BODY()

public:
	static UColorFormalParameter* New(UObject* Outer, FLinearColor DefaultVal);

	DF_PARAMETER_GETTER(UColorParameterValue, FLinearColor)
};
