// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ParameterIntegration/v2/ArraySelectorComboBox.h"

#include "FX/Niagara/v2/ParamUtil.h"
#include "FX/Niagara/v2/FormalParameter/ArraySelectorParameter.h"
#include "FX/Niagara/v2/ParameterValue/ArraySelectorParameterValue.h"
#include "DFUI/DFStyleUtil.h"
#include "Util/DFStatics.h"
#include "World/Launcher/LauncherManager.h"

FString UArraySelectorComboBox::NONE_OPTION_NAME = "__NONE__";

UArraySelectorComboBox::UArraySelectorComboBox()
{
	DFStyleUtil::ComboBox(this);
	OnSelectionChanged.AddUniqueDynamic(this, &UArraySelectorComboBox::HandleSelectionChangedInternal);
}

void UArraySelectorComboBox::DefaultStyle()
{
	DFStyleUtil::ComboBox(this);
}

void UArraySelectorComboBox::ReInitOptions(UGenericLauncherArray* Array)
{
	auto Names = ULauncherManager::GetInstance()->GetLauncherNames();
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

void UArraySelectorComboBox::ReInit()
{
	ReInitOptions(nullptr);
}

void UArraySelectorComboBox::Initialize(UAbstractParameterValue* Value)
{
	auto Array = UParamUtil::GetTypedValue<UArraySelectorParameterValue, UGenericLauncherArray*>(Value);
	ReInitOptions(Array);
	this->OnOpening.AddUniqueDynamic(this, &UArraySelectorComboBox::ReInit);
}

UAbstractParameterValue* UArraySelectorComboBox::GetValue(UObject* Outer)
{
	if(this->GetSelectedOption().Equals(NONE_OPTION_NAME))
	{
		return UArraySelectorParameterValue::New(Outer, nullptr);
	}
	auto Array = ULauncherManager::GetInstance()->FindLauncherArray(this->GetSelectedOption());
	if(!Array)
	{
		ReInitOptions(nullptr);
		return UArraySelectorParameterValue::New(Outer, nullptr);
	}
	return UArraySelectorParameterValue::New(Outer, Array);
}

void UArraySelectorComboBox::SetValue(UAbstractParameterValue* Value)
{
}

UWidget* UArraySelectorComboBox::AsWidget()
{
	return this;
}


void UArraySelectorComboBox::HandleSelectionChangedInternal(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if(SelectionType != ESelectInfo::Direct)
	{
		NotifyOfChange(this);
	}
}