// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/Niagara/v2/ParameterValue/FloatParameterValue.h"

#include "FX/Niagara/v2/ParamUtil.h"

TSharedPtr<FJsonObject> UFloatParameterValue::ToJson()
{
	auto Obj = new FJsonObject();
	Obj->SetNumberField("Value", Value);
	Obj->SetStringField("Type", UParamUtil::Name(FLOAT));
	return MakeShareable(Obj);
}

UAbstractParameterValue* UFloatParameterValue::Clone(UAbstractFormalParameter* Param)
{
	return New(Param, Value);
}

float UFloatParameterValue::ValueFromJson(TSharedPtr<FJsonObject> Json)
{
	return Json->GetNumberField("Value");
}

bool UFloatParameterValue::IsSerializable()
{
	return true;
}
