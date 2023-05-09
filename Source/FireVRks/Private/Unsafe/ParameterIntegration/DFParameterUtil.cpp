#include "Unsafe/ParameterIntegration/DFParameterUtil.h"

#include "UI/ParameterIntegration/DFUIParameterBindingWidgetBase.h"

void DFParameterUtil::SetContextValuesFromUI(MapParameterValueContext* Context, UPanelWidget* ParentWidget)
{
	for (UWidget* Widget : ParentWidget->GetAllChildren())
	{
		if(ParameterBindingWidget* PBW = Cast<UDFUIParameterBindingWidgetBase>(Widget))
		{
			PBW->SetValueInContext(Context);
		}
	}
}
