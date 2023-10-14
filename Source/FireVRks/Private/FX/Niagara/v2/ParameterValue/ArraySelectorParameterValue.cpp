// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/Niagara/v2/ParameterValue/ArraySelectorParameterValue.h"

UArraySelectorParameterValue* UArraySelectorParameterValue::New(UObject* Outer, UGenericLauncherArray* bArray)
{
	auto Val = NewObject<UArraySelectorParameterValue>(Outer, StaticClass());
	Val->Array = bArray;
	return Val;
}

UGenericLauncherArray* UArraySelectorParameterValue::Get()
{
	return Array;
}
