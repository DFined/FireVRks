#include "UI/ParameterIntegration/v2/ParameterBindingWidget.h"

#include "UI/DFUIUtil.h"
#include "UI/ParameterIntegration/v2/ParameterInputUI.h"

void UParameterBindingWidget::Setup(UAbstractFormalParameter* FParameter, UParameterValueContext* Context)
{
	this->Parameter = FParameter;
	this->Initialize(FParameter, Context);
	this->DefaultStyle();
}

void UParameterBindingWidget::DefaultStyle()
{
}

UAbstractFormalParameter* UParameterBindingWidget::GetParameter() const
{
	return Parameter;
}

void UParameterBindingWidget::OnChange()
{
	auto InputUI = DFUIUtil::AttemptFindWidgetByType<UParameterInputUI>(this);
	if (InputUI)
	{
		InputUI->OnChange();
	}
}
