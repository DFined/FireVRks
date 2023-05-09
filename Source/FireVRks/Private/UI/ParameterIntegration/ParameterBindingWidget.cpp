#include "UI/ParameterIntegration/ParameterBindingWidget.h"


void ParameterBindingWidget::SubscribeToChanges(WidgetCallbackWithValue* Callback)
{
	Callbacks.Add(Callback);
}
