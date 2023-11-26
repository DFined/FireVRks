#include "UI/ParameterIntegration/v2/ParameterBindingWidget.h"

#include "UI/DFUIUtil.h"
#include "UI/ParameterIntegration/v2/ParameterDrawType.h"
#include "UI/ParameterIntegration/v2/ParameterInputUI.h"

void UParameterBindingWidget::Setup(UAbstractFormalParameter* FParameter, UParameterValueContext* BContext, ParameterDrawType BDrawType)
{
	this->Parameter = FParameter;
	this->Context = BContext;
	this->DrawType = BDrawType;
	this->InitializeBindingWidget();
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
}
