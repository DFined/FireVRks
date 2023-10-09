// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/Niagara/v2/ParameterValue/BlockParameterValue.h"

UBlockParameterValue* UBlockParameterValue::New(UObject* Outer, bool Expanded, bool OverridesExpanded)
{
	auto Val = NewObject<UBlockParameterValue>(Outer, StaticClass());
	Val->Expanded = Expanded;
	Val->OverridesExpanded = OverridesExpanded;
	return Val;
}
