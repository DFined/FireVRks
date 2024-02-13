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
	UDFId* System;
public:
	static USystemInstantiationParameterValue* New(UObject* Outer, UParameterValueContext* Context, UDFId* System)
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

	UDFId* GetSystem() const
	{
		return System;
	}
	
	

	virtual TSharedPtr<FJsonObject> ToJson() override;

	virtual UAbstractParameterValue* Clone(UAbstractFormalParameter* Param) override;
};
