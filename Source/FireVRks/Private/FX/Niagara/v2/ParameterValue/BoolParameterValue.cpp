// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/Niagara/v2/ParameterValue/BoolParameterValue.h"

#include "FX/Niagara/v2/ParamUtil.h"

UBoolParameterValue* UBoolParameterValue::New(UObject* Outer, bool Value)
{
	auto Val = NewObject<UBoolParameterValue>(Outer, StaticClass());
	Val->Value = Value;
	return Val;
}

bool UBoolParameterValue::Get() const
{
	return Value;
}

TSharedPtr<FJsonObject> UBoolParameterValue::ToJson()
{
	auto Obj = new FJsonObject();
	Obj->SetBoolField("Value", Value);
	Obj->SetStringField("Type", UParamUtil::Name(BOOLEAN));
	return MakeShareable(Obj);
}

UAbstractParameterValue* UBoolParameterValue::Clone(UAbstractFormalParameter* Param)
{
	return New(Param, Value);
}

bool UBoolParameterValue::ValueFromJson(TSharedPtr<FJsonObject> Json)
{
	return Json->GetBoolField("Value");
}

