// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParameterValueContext.h"
#include "FormalParameter/AbstractFormalParameter.h"
#include "System/SubsystemParameterBindings.h"
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
	USubsystemParameterBindings* Bindings;
	
public:
	virtual UAbstractParameterValue* Get(UAbstractFormalParameter* Parameter) override;
	virtual void SetValue(UAbstractFormalParameter* Parameter, UAbstractParameterValue* Value) override;

	UAbstractFormalParameter* FindBinding(UDFId* Id)
	{
		auto Bind = Bindings->GetBindings().Find(Id);
		return Bind ? *Bind : nullptr;
	}

	static UBindingParameterValueContext* New(UObject* Outer){
		return NewObject<UBindingParameterValueContext>(Outer);
	}

	void SetOuterContext(UParameterValueContext* bOuterContext)
	{
		this->OuterContext = bOuterContext;
	}

	USubsystemParameterBindings* GetBindings() const
	{
		return Bindings;
	}

	void SetBindings(USubsystemParameterBindings* bBindings)
	{
		this->Bindings = bBindings;
	}
};
