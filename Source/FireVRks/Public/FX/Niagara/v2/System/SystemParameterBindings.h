// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FX/Niagara/v2/ParameterValue/AbstractParameterValue.h"
#include "UObject/Object.h"
#include "Util/DFId.h"
#include "SystemParameterBindings.generated.h"

/**
 * 
 */
UCLASS()
class FIREVRKS_API USystemParameterBindings : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<UDFId*, UDFId*> Bindings;

	UPROPERTY()
	TMap<UDFId*, UAbstractParameterValue*> ConstantValues;

public:
	TMap<UDFId*, UDFId*>& GetBindings() 
	{
		return Bindings;
	}

	TMap<UDFId*, UAbstractParameterValue*>& GetConstantValues() 
	{
		return ConstantValues;
	}

	static USystemParameterBindings* New(UObject* Outer)
	{
		return NewObject<USystemParameterBindings>(Outer, StaticClass());
	}
};
