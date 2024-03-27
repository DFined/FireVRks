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
	if (GetSelectedOption().Equals("None"))
	{
		return nullptr;
	}
	return Parameters[this->GetSelectedIndex() - 1];
}

void UParamBindingSelectionWidget::SetSelectedParam(UAbstractFormalParameter* Parameter)
{
	if (Parameter)
	{
		auto Num = Parameters.Find(Parameter);
		this->SetSelectedIndex(Num);
	}
	else
	{
		this->SetSelectedIndex(0);
	}
}

bool UParamBindingSelectionWidget::RemoveOptionParam(UAbstractFormalParameter* Parameter)
{
	auto Num = Parameters.Find(Parameter);
	if (Num != INDEX_NONE)
	{
		auto SelectedNum = GetSelectedIndex();
		Parameters.RemoveAt(Num);
		Num++;
		Options.RemoveAt(Num);
		RefreshOptions();
		if(Num == SelectedNum)
		{
			SetSelectedIndex(0);			
		}
	}
	return false;
}

void UParamBindingSelectionWidget::ReInit(TArray<UAbstractFormalParameter*>& bOptions)
{
	ClearOptions();
	AddOption("None");
	for (auto Param : bOptions)
	{
		AddOptionParam(Param);
	}
}

void UParamBindingSelectionWidget::RenameOptionParam(UAbstractFormalParameter* Param)
{
	auto Num = Parameters.Find(Param);
	if(Num != INDEX_NONE)
	{
		Num++;
		auto SelectedNum = GetSelectedIndex();
		Options[Num] = MakeShareable(new FString(Param->GetDisplayName()));
		RefreshOptions();
		if(SelectedNum == Num)
		{
			//If the option is already selected, it doesnt automatically update in the display, so we need to explicitly reset it
			SetSelectedOption(Param->GetDisplayName());
		}
	}
	
}
