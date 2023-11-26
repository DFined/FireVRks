// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ParameterIntegration/v2/ParamBindingSelectionWidget.h"

#include "FX/Niagara/v2/FormalParameter/AbstractFormalParameter.h"


void UParamBindingSelectionWidget::ReInit(TArray<UAbstractFormalParameter*>& Options)
{
	ClearOptions();
	for(auto Param : Options)
	{
		AddOption(Param->GetDisplayName());
	}
}

