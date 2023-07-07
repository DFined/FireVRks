#include "UI/ParameterIntegration/DFUIParameterBindingWidgetBase.h"

void UDFUIParameterBindingWidgetBase::BaseInit()
{
	GetOrCreateRoot();
}

void UDFUIParameterBindingWidgetBase::RebuildWidgetInternal()
{
}

UWidget* UDFUIParameterBindingWidgetBase::AsWidget()
{
	return this;
}

AbstractParameterValue* UDFUIParameterBindingWidgetBase::GetValue()
{
	return nullptr;
}

void UDFUIParameterBindingWidgetBase::SubscribeToChanges(WidgetCallbackWithValue* Callback)
{
	ParameterBindingWidget::SubscribeToChanges(Callback);
}

void UDFUIParameterBindingWidgetBase::CleanUp()
{
	ParameterBindingWidget::CleanUp();
}
