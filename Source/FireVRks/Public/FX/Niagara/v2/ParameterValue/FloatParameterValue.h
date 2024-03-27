// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractParameterValue.h"
#include "FloatParameterValue.generated.h"

/**
 * 
 */
UCLASS()
class FIREVRKS_API UFloatParameterValue : public UAbstractParameterValue
{
	GENERATED_BODY()
	
	float Value;
public:
	static UFloatParameterValue* New(UObject* Outer, float Value)
	{
		auto Val = NewObject<UFloatParameterValue>(Outer, StaticClass());
		Val->Value = Value;
		return Val;
	}

	float Get() const
	{
		return Value;
	}

	virtual TSharedPtr<FJsonObject> ToJson() override;

	virtual UAbstractParameterValue* Clone(UAbstractFormalParameter* Param) override;
	static float ValueFromJson(TSharedPtr<FJsonObject> Json);

	virtual bool IsSerializable() override;
};
