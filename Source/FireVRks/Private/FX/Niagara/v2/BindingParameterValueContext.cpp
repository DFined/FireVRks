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
	
	return Parameter->DefaultValue()->Clone(Parameter);
}

void UBindingParameterValueContext::SetValue(UAbstractFormalParameter* Parameter, UAbstractParameterValue* Value)
{
	this->Bindings->GetConstantValues().Add(Parameter->GetId(), Value)->Clone(Parameter);
}

TSharedPtr<FJsonObject> UBindingParameterValueContext::ToJson()
{
	auto Obj = new FJsonObject();
	Bindings->AddToJson(Obj);
	return MakeShareable(Obj);
}

UParameterValueContext* UBindingParameterValueContext::Clone(UObject* Parent)
{
	auto Context = New(Parent);
	Context->SetOuterContext(this->OuterContext);
	auto bBindings = USubsystemParameterBindings::Instance(Context);
	DFU::CloneMap(this->Bindings->GetBindings(), bBindings->GetBindings());
	DFU::CloneMap(this->Bindings->GetConstantValues(), bBindings->GetConstantValues());
	Context->SetBindings(bBindings);
	return Context;
}
