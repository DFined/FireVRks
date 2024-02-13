// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ParameterIntegration/v2/ParameterCreatorInput.h"

#include "FX/Niagara/v2/ParamUtil.h"
#include "DFUI/DFUI.h"

UPanelWidget* UParameterCreatorInput::MakeRootWidget()
{
	RootBox = DFUI::MakeWidget<UVerticalBox>(this);
	ParamNameInput = DFUI::NamedWidget<UEditableTextBox>(RootBox, "Parameter Name");
	DFStyleUtil::TextBoxStyle(ParamNameInput);
	ParamNameInput->SetText(FText::FromString("New Parameter"));
	
	ParamTypeInput = DFUI::NamedWidget<UComboBoxString>(RootBox, "Parameter Type");
	DFStyleUtil::ComboBox(ParamTypeInput);
	for(ParameterType Type : INSTANTIABLE_TYPES)
	{
		ParamTypeInput->AddOption(UParamUtil::Name(Type));
	}
	ParamTypeInput->SetSelectedIndex(0);
	
	ParamRequiredInput = DFUI::NamedWidget<UCheckBox>(RootBox, "Is required");
	DFStyleUtil::CheckBoxStyle(ParamRequiredInput);
	ParamRequiredInput->SetCheckedState(ECheckBoxState::Checked);
	
	return RootBox;
}

UPanelWidget* UParameterCreatorInput::GetMountingPoint()
{
	return RootBox;
}

FString UParameterCreatorInput::GetParamName()
{
	return ParamNameInput->GetText().ToString();
}

ParameterType UParameterCreatorInput::GetType()
{
	return UParamUtil::Type(ParamTypeInput->GetSelectedIndex());
}

bool UParameterCreatorInput::GetRequired()
{
	return ParamRequiredInput->IsChecked();
}

