// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/Niagara/v2/ParameterValue/EnumParameterValue.h"

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
