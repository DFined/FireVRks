#pragma once
#include "Components/Widget.h"
#include "FX/Niagara/v2/ParameterValueContext.h"
#include "FX/Niagara/v2/ParameterValue/AbstractParameterValue.h"
#include "UI/lib/DFStylableWidget.h"

class FIREVRKS_API WidgetWithValue : DFStylableWidget
{
public:
	virtual ~WidgetWithValue() override = default;
	virtual void Initialize(UAbstractParameterValue* Value) = 0;
	virtual void DefaultStyle() override;
	virtual UAbstractParameterValue* GetValue(UParameterValueContext* Context) = 0;
	virtual void SetValue(UAbstractParameterValue* Value) = 0;

	virtual void NotifyOfChange(UWidget* Self);

	virtual UWidget* AsWidget() = 0;
};
