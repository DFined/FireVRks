// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParameterValueContext.h"
#include "FormalParameter/AbstractFormalParameter.h"
#include "FormalParameter/ParameterType.h"
#include "Util/DFId.h"
#include "BindingParameterValueContext.generated.h"

/**
 * 
 */
UCLASS()
class FIREVRKS_API UBindingParameterValueContext : public UParameterValueContext
{
	GENERATED_BODY()

	UPROPERTY()
	UParameterValueContext* OuterContext;

	UPROPERTY()
	TMap<UDFId*, UAbstractFormalParameter*> Bindings;

	UPROPERTY()
	TArray<UAbstractFormalParameter*> OuterParameters;
	
public:
	virtual UAbstractParameterValue* Get(UAbstractFormalParameter* Parameter) override;
	virtual void SetValue(UAbstractFormalParameter* Parameter, UAbstractParameterValue* Value) override;

	TArray<UAbstractFormalParameter*>& GetOuterParameters()
	{
		return OuterParameters;
	}

	UAbstractFormalParameter* FindBinding(UDFId* Id)
	{
		auto Bind = Bindings.Find(Id);
		return Bind ? *Bind : nullptr;
	}

	void FindAvailableOuters(ParameterType Type, TArray<UAbstractFormalParameter*>& Results)
	{
		for(UAbstractFormalParameter* Param : OuterParameters)
		{
			if(Param->GetType() == Type)
			{
				Results.Add(Param);
			}
		}
	}

	static UBindingParameterValueContext* New(UObject* Outer){
		return NewObject<UBindingParameterValueContext>(Outer);
	}

	void SetOuterContext(UParameterValueContext* OuterContext)
	{
		this->OuterContext = OuterContext;
	}
};
