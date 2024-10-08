#include "UI/lib/ParameterBindingCheckbox.h"

#include "FX/Niagara/v2/ParamUtil.h"
#include "FX/Niagara/v2/ParameterValue/BoolParameterValue.h"
#include "DFUI/DFStyleUtil.h"

void UParameterBindingCheckbox::SetValue(UAbstractParameterValue* Value)
{
	SetCheckedState(UParamUtil::GetTypedValue<UBoolParameterValue, bool>(Value) ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);	
}

void UParameterBindingCheckbox::DefaultStyle()
{
	DFStyleUtil::CheckBoxStyle(this);	
}

UAbstractParameterValue* UParameterBindingCheckbox::GetValue(UObject* Outer)
{
	return UBoolParameterValue::New(Outer, this->IsChecked());
}

void UParameterBindingCheckbox::Initialize(UAbstractParameterValue* Value)
{
	SetValue(Value);
}

void UParameterBindingCheckbox::HandleCheckStateChanged(bool bIsChecked)
{
	NotifyOfChange(this);
}

UWidget* UParameterBindingCheckbox::AsWidget()
{
	return this;
}
