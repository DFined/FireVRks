// Fill out your copyright notice in the Description page of Project Settings.
#include "FX/Niagara/v2/FormalParameter/ArraySelectorParameter.h"
#include "FX/Niagara/v2/ParameterValue/ArraySelectorParameterValue.h"

UArraySelectorParameter* UArraySelectorParameter::New(UObject* Outer)
{
	auto Param = NewObject<UArraySelectorParameter>(Outer, StaticClass());
	Param->Default = UArraySelectorParameterValue::New(Param, nullptr);
	Param->Type = ARRAY_SELECTOR; 
	return Param;
}
