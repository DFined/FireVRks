#pragma once
#include "Components/PanelWidget.h"
#include "UI/ParameterIntegration/ParameterBindingWidget.h"

class UPanelWidget;

class DFParameterUtil
{
public:
	static void SetContextValuesFromUI(MapParameterValueContext* Context, UPanelWidget* ParentWidget);
};
