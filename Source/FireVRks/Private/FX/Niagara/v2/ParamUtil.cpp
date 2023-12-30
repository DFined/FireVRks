#include "FX/Niagara/v2/ParamUtil.h"

#include "FX/Niagara/v2/FormalParameter/BoolFormalParameter.h"
#include "FX/Niagara/v2/FormalParameter/ColorFormalParameter.h"
#include "FX/Niagara/v2/FormalParameter/FloatFormalParameter.h"
#include "FX/Niagara/v2/FormalParameter/IntFormalParameter.h"
#include "FX/Niagara/v2/ParameterValue/IntParameterValue.h"
#include "UI/DFUIUtil.h"
#include "UI/lib/ParameterBindingCheckbox.h"
#include "UI/lib/ParameterBindingComboBox.h"
#include "UI/lib/ValidatedTextBox/FColorTextBox.h"
#include "UI/lib/ValidatedTextBox/FloatTextBox.h"
#include "UI/lib/ValidatedTextBox/IntTextBox.h"
#include "UI/ParameterIntegration/v2/ArraySelectorComboBox.h"
#include "UI/ParameterIntegration/v2/ParameterBindingWidget.h"

template <class OuterType, typename InnerType>
InnerType UParamUtil::GetTypedValue(UAbstractParameterValue* Value)
{
	return Cast<OuterType>(Value)->Get();
}

WidgetWithValue* UParamUtil::GetValueWidget(UUserWidget* Outer, ParameterType Type)
{
	WidgetWithValue* Widget = nullptr;
	switch (Type)
	{
		case INTEGER:
			{
				Widget = UDFUIUtil::MakeWidget<UIntTextBox>(Outer->WidgetTree);
				break;
			}
		case BOOLEAN:
			{
				Widget = UDFUIUtil::MakeWidget<UParameterBindingCheckbox>(Outer->WidgetTree);
				break;
			}
		case FLOAT:
			{
				Widget = UDFUIUtil::MakeWidget<UFloatTextBox>(Outer->WidgetTree);
				break;
			}
		case COLOR:
			{
				Widget = UDFUIUtil::MakeWidget<UFColorTextBox>(Outer->WidgetTree);
				break;
			}
		case ENUM:
			{
				Widget = UDFUIUtil::MakeWidget<UParameterBindingComboBox>(Outer->WidgetTree);
				break;
			}
		case ARRAY_SELECTOR:
			{
				Widget = UDFUIUtil::MakeWidget<UArraySelectorComboBox>(Outer->WidgetTree);
				break;
			}
	}
	return Widget;
}

void UParamUtil::WriteContainerToContext(UPanelWidget* Container, UParameterValueContext* Context)
{
	for (UWidget* Child : Container->GetAllChildren())
	{
		if(auto Widget = Cast<UParameterBindingWidget>(Child))
		{
			Widget->WriteToContext(Context);
		}			
	}
}

UAbstractFormalParameter* UParamUtil::NewParam(UObject* Outer, FString Name, bool Required, ParameterType Type)
{
	switch (Type)
	{
		case INTEGER: return Setup(Name, Required, UIntFormalParameter::New(Outer, 1));
		case FLOAT: return Setup(Name, Required, UFloatFormalParameter::New(Outer, 1.0));
		case COLOR: return Setup(Name, Required, UColorFormalParameter::New(Outer, FLinearColor(255, 0, 0)));
		case BOOLEAN: return Setup(Name, Required, UBoolFormalParameter::New(Outer, false));
		default: return nullptr;
	}
}

