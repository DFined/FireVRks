// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/Niagara/v2/BindingParameterValueContext.h"

#include "FX/Niagara/v2/FormalParameter/AbstractFormalParameter.h"

UAbstractParameterValue* UBindingParameterValueContext::Get(UAbstractFormalParameter* Parameter)
{
	if (auto BoundTo = Bindings->GetBindings().Find(Parameter->GetId()))
	{
		return OuterContext->Get(*BoundTo);
	}
	if (auto Constant = Bindings->GetConstantValues().Find(Parameter->GetId()))
	{
		return *Constant;
	}
	return Parameter->DefaultValue();
}

void UBindingParameterValueContext::SetValue(UAbstractFormalParameter* Parameter, UAbstractParameterValue* Value)
{
	throw std::runtime_error("Setting values in binding context is not implemented");
}
