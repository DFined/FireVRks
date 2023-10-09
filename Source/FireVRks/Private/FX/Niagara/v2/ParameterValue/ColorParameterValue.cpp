// Fill out your copyright notice in the Description page of Project Settings.

#include "FX/Niagara/v2/ParameterValue//ColorParameterValue.h"

UColorParameterValue* UColorParameterValue::New(UObject* Outer, FLinearColor Color)
{
	auto Val = NewObject<UColorParameterValue>(Outer, StaticClass());
	Val->Color = Color;
	return Val;
}
