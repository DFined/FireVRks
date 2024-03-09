// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/Niagara/v2/System/SubsystemParameterBindings.h"

#include "FX/Niagara/v2/ParamUtil.h"

void USubsystemParameterBindings::AddToJson(FJsonObject* Obj)
{
	auto BindingsJson = new FJsonObject();
	auto BindKeys = TArray<FDFId>();
	GetBindings().GetKeys(BindKeys);
	for (FDFId bId : BindKeys)
	{
		BindingsJson->SetStringField(bId.GetId(), (*GetBindings().Find(bId))->GetId().GetId());
	}
	Obj->SetObjectField(BindingsFieldName, MakeShareable(BindingsJson));

	auto ConstantsJson = new FJsonObject();
	auto ConstantKeys = TArray<FDFId>();
	GetConstantValues().GetKeys(ConstantKeys);
	for (auto bId : ConstantKeys)
	{
		ConstantsJson->SetObjectField(bId.GetId(), (*GetConstantValues().Find(bId))->ToJson());
	}

	Obj->SetObjectField(ConstantsFieldName, MakeShareable(ConstantsJson));
}

USubsystemParameterBindings* USubsystemParameterBindings::GetFromJson(
	TSharedPtr<FJsonObject> Json, UObject* Outer, TMap<FDFId, UAbstractFormalParameter*>& Outers
) {
	auto Bindings = Instance(Outer);
	for (auto Entry : Json->GetObjectField(ConstantsFieldName)->Values)
	{
		auto Key = FDFId::Named(Entry.Key);
		auto Value = UParamUtil::ValueFromJson(Entry.Value->AsObject(), Bindings);
		Bindings->ConstantValues.Add(*Key.Get(), Value);
	}
	auto BindingsMap = Json->GetObjectField(BindingsFieldName)->Values;
	TArray<FString> SourceParams = TArray<FString>();
	BindingsMap.GetKeys(SourceParams);
	for (FString fSource : SourceParams)
	{
		TSharedPtr<FDFId> fKey = FDFId::Named(fSource);
		auto ValueId = FDFId::Named(*BindingsMap.Find(fSource)->Get()->AsString());
		auto fValue = *Outers.Find(*ValueId);
		Bindings->Bindings.Add(*fKey.Get(), fValue);
	
	}
	return Bindings;
}
