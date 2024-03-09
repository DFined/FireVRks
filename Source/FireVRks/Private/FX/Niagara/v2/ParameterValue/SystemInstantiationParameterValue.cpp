// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/Niagara/v2/ParameterValue/SystemInstantiationParameterValue.h"

#include "FX/Niagara/v2/ParamUtil.h"

TSharedPtr<FJsonObject> USystemInstantiationParameterValue::ToJson()
{
	auto Obj = new FJsonObject();
	Obj->SetStringField("Type", UParamUtil::Name(SYSTEM_INSTANTIATION));
	Obj->SetStringField("SystemId", System.GetId());
	Obj->SetObjectField("Context", Context->ToJson());
	return MakeShareable(Obj);
}

UAbstractParameterValue* USystemInstantiationParameterValue::Clone(UAbstractFormalParameter* Param)
{
	return New(Param, Context, System);
}
