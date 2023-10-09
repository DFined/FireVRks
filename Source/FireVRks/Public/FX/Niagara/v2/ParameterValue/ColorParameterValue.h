// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FX/Niagara/v2/ParameterValue/AbstractParameterValue.h"
#include "ColorParameterValue.generated.h"

/**
 * 
 */
UCLASS()
class FIREVRKS_API UColorParameterValue : public UAbstractParameterValue
{
	GENERATED_BODY()

	FLinearColor Color;

public:
	static UColorParameterValue* New(UObject* Outer, FLinearColor Color);

	FLinearColor Get() const
	{
		return Color;
	}
};
