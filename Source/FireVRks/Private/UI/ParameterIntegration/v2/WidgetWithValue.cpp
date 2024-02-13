#include "UI/ParameterIntegration/v2/WidgetWithValue.h"

#include "DFUI/DFUI.h"
#include "UI/ParameterIntegration/v2/ParameterLineBindingWidget.h"

void WidgetWithValue::DefaultStyle()
{
}

void WidgetWithValue::NotifyOfChange(UWidget* Self)
{
	auto ParentUi = DFUI::AttemptFindWidgetByType<UParameterLineBindingWidget>(Self);
	ParentUi->OnChange();
}

