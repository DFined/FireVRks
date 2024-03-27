// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/Niagara/v2/ParameterValue/ListParameterValue.h"

#include "FX/Niagara/v2/ParamUtil.h"

UAbstractParameterValue* UListParameterValue::FromJson(TSharedPtr<FJsonObject> Json, UObject* Outer,  TMap<FDFId, UAbstractFormalParameter*>& Outers)
{
	auto Value = New(Outer);
	for(TSharedPtr<FJsonValue> MPtr : Json->GetArrayField("Value"))
	{
		Value->Values.Add(UParameterValueContext::FromJson(MPtr->AsObject(), Outer, Outers));
	}
	return Value;
}

TSharedPtr<FJsonObject> UListParameterValue::ToJson()
{
	auto Obj = new FJsonObject();
	TArray<TSharedPtr<FJsonValue>> Arr = TArray<TSharedPtr<FJsonValue>>();
	for(auto Val : Values)
	{
		Arr.Add(MakeShareable(new FJsonValueObject(Val->ToJson())));
	}
	Obj->SetArrayField("Value", Arr);
	Obj->SetStringField("Type", UParamUtil::Name(LIST));
	return MakeShareable(Obj);
}

UAbstractParameterValue* UListParameterValue::Clone(UAbstractFormalParameter* Param)
{
	auto Res = New(Param);
	for(auto Val : Values)
	{
		Res->AddValue(Val);		
	}
	return Res;
}

bool UListParameterValue::IsSerializable()
{
	return true;
}
