#pragma once
#include "FX/Niagara/SystemSettings/ParameterValues/AbstractParameterValue.h"
#include "UI/lib/ValidatedTextBox/ValidatedTextBox.h"

class ParamUtilObject
{
public:
	explicit ParamUtilObject(
		ParameterBindingWidget*(* const CreateInput)(UWidgetTree*), 
		FString (* const ToString)(AbstractParameterValue*)
	) : CreateInput(CreateInput), ToString(ToString)
	{
	}

	ParameterBindingWidget* (* const CreateInput)(UWidgetTree*);
	FString (* const ToString)(AbstractParameterValue*);
};
