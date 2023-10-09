// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/Niagara/v2/FormalParameter/FloatFormalParameter.h"

#include "FX/Niagara/v2/ParameterValue/FloatParameterValue.h"

UFloatFormalParameter* UFloatFormalParameter::New(UObject* Outer, float Default)
{
	auto Param = NewObject<UFloatFormalParameter>(Outer, StaticClass());
	Param->Default = UFloatParameterValue::New(Outer, Default);
	Param->Type=FLOAT;
	return Param;
}
