// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/Niagara/v2/ParameterValue/ArraySelectorParameterValue.h"

#include "FX/Niagara/v2/ParamUtil.h"

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

TSharedPtr<FJsonObject> UArraySelectorParameterValue::ToJson()
{
	auto Obj = new FJsonObject();
	Obj->SetStringField("Type", UParamUtil::Name(ARRAY_SELECTOR));
	if(Array)
	{
		Obj->SetStringField("Value", Array->GetName());
	}
	return MakeShareable(Obj);
}

UAbstractParameterValue* UArraySelectorParameterValue::Clone(UAbstractFormalParameter* Param)
{
	return New(Param, Array);
}
