// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ParameterIntegration/v2/ArraySelectorComboBox.h"

#include "FX/Niagara/v2/ParamUtil.h"
#include "FX/Niagara/v2/FormalParameter/ArraySelectorParameter.h"
#include "FX/Niagara/v2/ParameterValue/ArraySelectorParameterValue.h"
#include "UI/lib/DFStyleUtil.h"
#include "Util/DFStatics.h"

FString UArraySelectorComboBox::NONE_OPTION_NAME = "__NONE__";

UArraySelectorComboBox::UArraySelectorComboBox()
{
	DFStyleUtil::ComboBox(this);
}

void UArraySelectorComboBox::DefaultStyle()
{
	DFStyleUtil::ComboBox(this);
}

void UArraySelectorComboBox::ReInitOptions(UGenericLauncherArray* Array)
{
	auto Names = UDFStatics::LAUNCHER_MANAGER->GetLauncherNames();
	this->ClearOptions();
	if (Names.IsEmpty())
	{
		this->AddOption(NONE_OPTION_NAME);
	}
	for (FString Name : Names)
	{
		this->AddOption(Name);
	}
	if (Array && Names.Contains(Array->GetArrayName()))
	{
		this->SetSelectedOption(Array->GetArrayName());
	}
	else
	{
		this->SetSelectedIndex(0);
	}
}

void UArraySelectorComboBox::Initialize(UAbstractParameterValue* Value)
{
	auto Array = UParamUtil::GetTypedValue<UArraySelectorParameterValue, UGenericLauncherArray*>(Value);
	ReInitOptions(Array);
}

UAbstractParameterValue* UArraySelectorComboBox::GetValue(UParameterValueContext* Context)
{
	if(this->GetSelectedOption().Equals(NONE_OPTION_NAME))
	{
		return UArraySelectorParameterValue::New(Context, nullptr);
	}
	auto Array = UDFStatics::GetLauncherManager()->FindLauncherArray(this->GetSelectedOption());
	if(!Array)
	{
		ReInitOptions(nullptr);
		return UArraySelectorParameterValue::New(Context, nullptr);
	}
	return UArraySelectorParameterValue::New(Context, Array);
}

void UArraySelectorComboBox::SetValue(UAbstractParameterValue* Value)
{
}

UWidget* UArraySelectorComboBox::AsWidget()
{
	return this;
}
