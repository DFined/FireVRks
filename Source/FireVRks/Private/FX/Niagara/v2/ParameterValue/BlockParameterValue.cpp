// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/Niagara/v2/ParameterValue/BlockParameterValue.h"

#include "FX/Niagara/v2/ParamUtil.h"

bool UBlockParameterValue::ValueFromJson(TSharedPtr<FJsonObject> Json)
{
	return Json->GetBoolField("Expanded");
}

UBlockParameterValue* UBlockParameterValue::New(UObject* Outer, bool Expanded, bool OverridesExpanded)
{
	auto Val = NewObject<UBlockParameterValue>(Outer, StaticClass());
	Val->Expanded = Expanded;
	Val->OverridesExpanded = OverridesExpanded;
	return Val;
}

TSharedPtr<FJsonObject> UBlockParameterValue::ToJson()
{
	auto Obj = new FJsonObject();
	Obj->SetStringField("Type", UParamUtil::Name(BLOCK));
	Obj->SetBoolField("Expanded", Expanded);
	Obj->SetBoolField("OverridesExpanded", OverridesExpanded);
	return MakeShareable(Obj);
}

UAbstractParameterValue* UBlockParameterValue::Clone(UAbstractFormalParameter* Param)
{
	return New(Param, Expanded, OverridesExpanded);
}

void UBlockParameterValue::SetExpanded(bool bExpanded)
{
	Expanded = bExpanded;
}

void UBlockParameterValue::SetOverridesExpanded(bool bOverridesExpanded)
{
	OverridesExpanded = bOverridesExpanded;
}
