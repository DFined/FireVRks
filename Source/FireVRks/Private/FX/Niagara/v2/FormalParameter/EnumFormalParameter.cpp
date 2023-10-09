// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/Niagara/v2/FormalParameter/EnumFormalParameter.h"

UEnumFormalParameter* UEnumFormalParameter::New(UObject* Outer, EnumLikeValue* DefaultVal)
{
	auto Param = NewObject<UEnumFormalParameter>(Outer, StaticClass());
	Param->Default = UEnumParameterValue::New(Param, DefaultVal);
	Param->ValueType = DefaultVal->GetParent();
	Param->Type = ENUM;
	return Param;
}
