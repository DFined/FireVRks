#pragma once

class ParameterBindingWidget;
class AbstractParameterValue;

class WidgetCallbackWithValue
{
public:
	virtual ~WidgetCallbackWithValue() = default;
	virtual void Callback(ParameterBindingWidget* Widget, AbstractParameterValue* Value) = 0;
};
