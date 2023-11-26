#include "UI/ParameterIntegration/v2/WidgetWithValue.h"

#include "UI/ParameterIntegration/v2/ParameterInputUI.h"
#include "UI/DFUIUtil.h"

void WidgetWithValue::DefaultStyle()
{
}

void WidgetWithValue::NotifyOfChange(UWidget* Self)
{
	auto ParentUi = UDFUIUtil::AttemptFindWidgetByType<UParameterControlWidget>(Self);
	ParentUi->OnChange();
}

