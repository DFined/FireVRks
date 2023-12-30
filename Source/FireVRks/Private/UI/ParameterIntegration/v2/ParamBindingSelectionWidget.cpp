// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ParameterIntegration/v2/ParamBindingSelectionWidget.h"

#include "FX/Niagara/v2/FormalParameter/AbstractFormalParameter.h"


void UParamBindingSelectionWidget::AddOptionParam(UAbstractFormalParameter* Parameter)
{
	Parameters.Add(Parameter);
	this->AddOption(Parameter->GetDisplayName());
}

UAbstractFormalParameter* UParamBindingSelectionWidget::GetSelectedParam()
{
	if(GetSelectedOption().Equals("None"))
	{
		return nullptr;
	}
	return Parameters[this->GetSelectedIndex()-1];
}

void UParamBindingSelectionWidget::SetSelectedParam(UAbstractFormalParameter* Parameter)
{
	if (Parameter)
	{
		auto Num = Parameters.Find(Parameter);
		this->SetSelectedIndex(Num);
	} else
	{
		this->SetSelectedIndex(0);
	}
}

void UParamBindingSelectionWidget::RemoveOptionParam(UAbstractFormalParameter* Parameter)
{
	auto Num = Parameters.Find(Parameter);
	Parameters.RemoveAt(Num);
	SetSelectedParam(nullptr);
}

void UParamBindingSelectionWidget::ReInit(TArray<UAbstractFormalParameter*>& bOptions)
{
	ClearOptions();
	AddOption("None");
	for(auto Param : bOptions)
	{
		AddOptionParam(Param);
	}
}

