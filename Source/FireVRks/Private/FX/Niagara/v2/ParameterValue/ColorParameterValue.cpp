// Fill out your copyright notice in the Description page of Project Settings.

#include "FX/Niagara/v2/ParameterValue//ColorParameterValue.h"

#include "FX/Niagara/v2/ParamUtil.h"

UColorParameterValue* UColorParameterValue::New(UObject* Outer, FLinearColor Color)
{
	auto Val = NewObject<UColorParameterValue>(Outer, StaticClass());
	Val->Color = Color;
	return Val;
}

TSharedPtr<FJsonObject> UColorParameterValue::ToJson()
{
	auto Obj = new FJsonObject();
	Obj->SetNumberField("R", Color.R);
	Obj->SetNumberField("G", Color.G);
	Obj->SetNumberField("B", Color.B);
	Obj->SetStringField("Type", UParamUtil::Name(COLOR));
	return MakeShareable(Obj);
}

UAbstractParameterValue* UColorParameterValue::Clone(UAbstractFormalParameter* Param)
{
	return New(Param, Color);
}

FLinearColor UColorParameterValue::ValueFromJson(TSharedPtr<FJsonObject> Json)
{
	return FLinearColor(Json->GetNumberField("R"), Json->GetNumberField("G"), Json->GetNumberField("B"));
}

