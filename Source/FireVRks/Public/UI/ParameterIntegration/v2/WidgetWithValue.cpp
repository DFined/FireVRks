#include "WidgetWithValue.h"

#include "ParameterInputUI.h"

void WidgetWithValue::DefaultStyle()
{
}

void WidgetWithValue::NotifyOfChange(UWidget* Self)
{
	auto ParentUi = DFUIUtil::AttemptFindWidgetByType<UParameterInputUI>(Self);
	ParentUi->OnChange();
}

