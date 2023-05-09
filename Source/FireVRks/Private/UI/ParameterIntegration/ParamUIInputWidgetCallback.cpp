#include "UI/ParameterIntegration/ParamUIInputWidgetCallback.h"

void ParamUIInputWidgetCallback::Callback(ParameterBindingWidget* Widget, AbstractParameterValue* Value)
{
	UI->OnChildWidgetValueChange(Widget, Value);
}
