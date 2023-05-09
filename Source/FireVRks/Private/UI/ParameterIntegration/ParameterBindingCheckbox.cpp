#include "UI/ParameterIntegration/ParameterBindingCheckbox.h"

#include "Unsafe/DFStyleUtil.h"
#include "Unsafe/ParameterIntegration/ParameterTypingUtil.h"

void UParameterBindingCheckbox::SetValue(AbstractParameterValue* Value)
{
	SetCheckedState(ParameterTypingUtil::ToValue<bool>(Value)->Get() ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);	
}

void UParameterBindingCheckbox::DefaultStyle()
{
	DFStyleUtil::CheckBoxStyle(this);	
}

UWidget* UParameterBindingCheckbox::AsWidget()
{
	return this;
}

AbstractParameterValue* UParameterBindingCheckbox::GetValue()
{
	return new ParameterValue(this->IsChecked(), DFType::TYPED_BOOL_PARAMETER, false);
}


void UParameterBindingCheckbox::HandleCheckStateChanged(bool bIsChecked)
{
	OnChange();
}
