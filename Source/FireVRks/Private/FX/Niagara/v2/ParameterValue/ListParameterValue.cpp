// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/Niagara/v2/ParameterValue/ListParameterValue.h"

#include "FX/Niagara/v2/ParamUtil.h"
#include "Util/DFJsonUtil.h"

UAbstractParameterValue* UListParameterValue::FromJson(TSharedPtr<FJsonObject> Json, UObject* Outer)
{
	auto Value = New(Outer);
	DFJsonUtil::GetArrayField<UParameterValueContext>(Json, "Value", Value, Value->Values);
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
