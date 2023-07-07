#include "UI/ParameterIntegration/ParameterBindingWidget.h"


void ParameterBindingWidget::SubscribeToChanges(WidgetCallbackWithValue* Callback)
{
	Callbacks.Add(Callback);
}

void ParameterBindingWidget::CleanUp()
{
	Callbacks.Empty();
	Parameter = nullptr;
}
