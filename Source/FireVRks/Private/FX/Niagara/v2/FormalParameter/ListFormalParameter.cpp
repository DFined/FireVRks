// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/Niagara/v2/FormalParameter/ListFormalParameter.h"

#include "FX/Niagara/v2/ParameterValue/ListParameterValue.h"

UListFormalParameter* UListFormalParameter::New(UObject* Outer, UAbstractFormalParameter* ChildType)
{
	auto Param = NewObject<UListFormalParameter>(Outer, StaticClass());
	Param->Default = UListParameterValue::New(Param);
	Param->Type = LIST;
	Param->ChildType = ChildType;
	return Param;
}
