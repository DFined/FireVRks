// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "AbstractParameterValue.h"
#include "ListParameterValue.generated.h"

UCLASS()
class FIREVRKS_API UListParameterValue : public UAbstractParameterValue
{
	GENERATED_BODY()
	
	TArray<UParameterValueContext*> Values;

public:
	TArray<UParameterValueContext*> Get() const
	{
		return Values;
	}

	void AddValue(UParameterValueContext* Context)
	{
		Values.Add(Context);
	}

	static UListParameterValue* New(UObject* Outer)
	{
		auto Value = NewObject<UListParameterValue>(Outer, StaticClass());
		Value->Values = TArray<UParameterValueContext*>();
		return Value;
	}
	
	
};
