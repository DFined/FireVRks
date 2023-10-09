// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/Niagara/v2/FormalParameter/ColorFormalParameter.h"

UColorFormalParameter* UColorFormalParameter::New(UObject* Outer, FLinearColor DefaultVal)
{
	auto Param = NewObject<UColorFormalParameter>(Outer, StaticClass());
	Param->Default = UColorParameterValue::New(Outer, DefaultVal);
	Param->Type = COLOR;
	return Param;
}
