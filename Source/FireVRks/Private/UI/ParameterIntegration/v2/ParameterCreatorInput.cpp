// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ParameterIntegration/v2/ParameterCreatorInput.h"

#include "FX/Niagara/v2/ParamUtil.h"
#include "UI/DFUIUtil.h"

UPanelWidget* UParameterCreatorInput::MakeRootWidget(UWidgetTree* Tree)
{
	RootBox = UDFUIUtil::MakeWidget<UVerticalBox>(Tree);
	ParamNameInput = UDFUIUtil::NamedWidget<UEditableTextBox>(RootBox, Tree, "Parameter Name");
	DFStyleUtil::TextBoxStyle(ParamNameInput);
	ParamNameInput->SetText(FText::FromString("New Parameter"));
	
	ParamTypeInput = UDFUIUtil::NamedWidget<UComboBoxString>(RootBox, Tree, "Parameter Type");
	DFStyleUtil::ComboBox(ParamTypeInput);
	for(ParameterType Type : INSTANTIABLE_TYPES)
	{
		ParamTypeInput->AddOption(UParamUtil::Name(Type));
	}
	ParamTypeInput->SetSelectedIndex(0);
	
	ParamRequiredInput = UDFUIUtil::NamedWidget<UCheckBox>(RootBox, Tree, "Is required");
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

