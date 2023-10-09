// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractParameterValue.h"
#include "BoolParameterValue.generated.h"

UCLASS()
class FIREVRKS_API UBoolParameterValue : public UAbstractParameterValue
{
	GENERATED_BODY()

	bool Value;
	
public:
	static UBoolParameterValue* New(UObject* Outer, bool Value);

	bool Get() const;
};
