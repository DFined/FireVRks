// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "AbstractParameterValue.h"
#include "FX/Niagara/v2/ParameterValueContext.h"
#include "ListParameterValue.generated.h"

UCLASS()
class FIREVRKS_API UListParameterValue : public UAbstractParameterValue
{
	GENERATED_BODY()

	UPROPERTY()
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

	static UAbstractParameterValue* FromJson(TSharedPtr<FJsonObject> Json, UObject* Outer, TMap<FDFId, UAbstractFormalParameter*>& Outers);

	static UListParameterValue* New(UObject* Outer)
	{
		auto Value = NewObject<UListParameterValue>(Outer, StaticClass());
		Value->Values = TArray<UParameterValueContext*>();
		return Value;
	}

	virtual TSharedPtr<FJsonObject> ToJson() override;

	virtual UAbstractParameterValue* Clone(UAbstractFormalParameter* Param) override;
};
