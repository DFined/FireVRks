// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/Niagara/v2/ParameterValue/EnumParameterValue.h"

#include "FX/Niagara/v2/ParamUtil.h"

UEnumParameterValue* UEnumParameterValue::New(UObject* Outer, EnumLikeValue* Value)
{
	auto Val = NewObject<UEnumParameterValue>(Outer, StaticClass());
	Val->Value = Value;
	return Val;
}

EnumLikeValue* UEnumParameterValue::Get() const
{
	return Value;
}

TSharedPtr<FJsonObject> UEnumParameterValue::ToJson()
{
	auto Obj = new FJsonObject();
	Obj->SetStringField("Value", Value->GetName());
	Obj->SetStringField("Type", UParamUtil::Name(ENUM));
	return MakeShareable(Obj);
}

UAbstractParameterValue* UEnumParameterValue::Clone(UAbstractFormalParameter* Param)
{
	return New(Param, Value);
}
