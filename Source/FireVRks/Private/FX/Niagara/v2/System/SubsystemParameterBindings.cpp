// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/Niagara/v2/System/SubsystemParameterBindings.h"

#include "FX/Niagara/v2/ParamUtil.h"

void USubsystemParameterBindings::AddToJson(FJsonObject* Obj)
{
	auto BindingsJson = new FJsonObject();
	auto BindKeys = TArray<UDFId*>();
	GetBindings().GetKeys(BindKeys);
	for(auto bId : BindKeys)
	{
		BindingsJson->SetStringField(bId->GetId(), (*GetBindings().Find(bId))->GetId()->GetId());
	}
	Obj->SetObjectField("Bindings", MakeShareable(BindingsJson));

	auto ConstantsJson = new FJsonObject();
	auto ConstantKeys = TArray<UDFId*>();
	GetConstantValues().GetKeys(ConstantKeys);
	for(auto bId : ConstantKeys)
	{
		ConstantsJson->SetObjectField(bId->GetId(), (*GetConstantValues().Find(bId))->ToJson());
	}

	Obj->SetObjectField(ConstantsFieldName, MakeShareable(ConstantsJson));
}

USubsystemParameterBindings* USubsystemParameterBindings::GetFromJson(TSharedPtr<FJsonObject> Json, UObject* Outer)
{
	auto Bindings = Instance(Outer);
	for(auto Entry : Json->GetObjectField(ConstantsFieldName)->Values)
	{
		auto Key = UDFId::Named(Bindings, Entry.Key);
		auto Value = UParamUtil::ValueFromJson(Json, Bindings);
		Bindings->ConstantValues.Add(Key, Value);
	}
	for(auto Entry : Json->Values)
	{
		auto Key = UDFId::Named(Bindings, Entry.Key);
		auto Value = UAbstractFormalParameter::FromJson(Json, Outer);
		Bindings->Bindings.Add(Key, Value);
	}
	return Bindings;
}
