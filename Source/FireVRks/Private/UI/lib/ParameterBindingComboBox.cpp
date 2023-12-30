#include "UI/lib/ParameterBindingComboBox.h"

#include "FX/Niagara/SystemSettings/Enums/EnumLikeValue.h"
#include "FX/Niagara/v2/ParamUtil.h"
#include "FX/Niagara/v2/ParameterValue/EnumParameterValue.h"
#include "UI/lib/DFStyleUtil.h"

void UParameterBindingComboBox::Initialize(UAbstractParameterValue* Value)
{
	auto Val = Cast<UEnumParameterValue>(Value);
	
	EnumType = Val->Get()->GetParent();
	auto Names = EnumType->GetNames();
	for(FString Name: *Names)
	{
		this->AddOption(Name);		
	}
	SetValue(Value);
}


void UParameterBindingComboBox::SetValue(UAbstractParameterValue* Value)
{
	SetSelectedOption(UParamUtil::GetTypedValue<UEnumParameterValue, EnumLikeValue*>(Value)->Name);
}

void UParameterBindingComboBox::DefaultStyle()
{
	DFStyleUtil::ComboBox(this);
}

UAbstractParameterValue* UParameterBindingComboBox::GetValue(UObject* Outer)
{
	FString Value = this->GetSelectedOption();
	return UEnumParameterValue::New(Outer, EnumType->Get(Value));
}

UWidget* UParameterBindingComboBox::AsWidget()
{
	return this;
}
