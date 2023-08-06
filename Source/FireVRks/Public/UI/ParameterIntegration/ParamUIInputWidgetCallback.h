#pragma once
#include "EffectParameterInputUI.h"
#include "WidgetCallbackWithValue.h"

class ParamUIInputWidgetCallback : public WidgetCallbackWithValue
{
public:
	explicit ParamUIInputWidgetCallback(UParameterInputUI* UI)
		: UI(UI)
	{
	}

	UParameterInputUI* UI;

	virtual void Callback(ParameterBindingWidget* Widget, AbstractParameterValue* Value) override;
};
