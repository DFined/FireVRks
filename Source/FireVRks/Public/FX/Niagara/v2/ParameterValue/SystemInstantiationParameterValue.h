// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractParameterValue.h"
#include "FX/Niagara/v2/ParameterValueContext.h"
#include "FX/Niagara/v2/System/EffectSystem.h"
#include "SystemInstantiationParameterValue.generated.h"

/**
 * 
 */
UCLASS()
class FIREVRKS_API USystemInstantiationParameterValue : public UAbstractParameterValue
{
	GENERATED_BODY()

	UPROPERTY()
	UParameterValueContext* Context;

	UPROPERTY()
	FDFId System;
public:
	static USystemInstantiationParameterValue* New(UObject* Outer, UParameterValueContext* Context, FDFId System)
	{
		auto Val = NewObject<USystemInstantiationParameterValue>(Outer, StaticClass());
		Val->Context = Context;
		Val->System = System;
		return Val;
	}

	UParameterValueContext* GetContext() const
	{
		return Context;
	}

	FDFId GetSystem() const
	{
		return System;
	}

	void SetSystem(const FDFId& bSystem);

	virtual TSharedPtr<FJsonObject> ToJson() override;

	virtual UAbstractParameterValue* Clone(UAbstractFormalParameter* Param) override;

	virtual bool IsSerializable() override;
};
