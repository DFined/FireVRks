#include "UI/ParameterIntegration/v2/WidgetWithValue.h"

#include "UI/DFUIUtil.h"
#include "UI/ParameterIntegration/v2/ParameterLineBindingWidget.h"

void WidgetWithValue::DefaultStyle()
{
}

void WidgetWithValue::NotifyOfChange(UWidget* Self)
{
	auto ParentUi = UDFUIUtil::AttemptFindWidgetByType<UParameterLineBindingWidget>(Self);
	ParentUi->OnChange();
}

