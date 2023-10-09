// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/Niagara/v2/ParameterValue/BoolParameterValue.h"

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
