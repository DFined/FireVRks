#include "FX/Niagara/v2/ParamUtil.h"

#include "FX/Niagara/v2/ParameterValue/IntParameterValue.h"
#include "UI/DFUIUtil.h"
#include "UI/lib/ParameterBindingCheckbox.h"
#include "UI/lib/ParameterBindingComboBox.h"
#include "UI/lib/ValidatedTextBox/FColorTextBox.h"
#include "UI/lib/ValidatedTextBox/FloatTextBox.h"
#include "UI/lib/ValidatedTextBox/IntTextBox.h"
#include "UI/ParameterIntegration/v2/ParameterBindingWidget.h"

template <class OuterType, typename InnerType>
InnerType UParamUtil::GetTypedValue(UAbstractParameterValue* Value)
{
	return Cast<OuterType>(Value)->Get();
}

template <class Type>
Type* UParamUtil::Setup(FString Id, FString Name, bool Required, Type* Parameter)
{
	Parameter->SetRequired(Required);
	Parameter->SetDisplayName(Name);
	Parameter->SetId(UDFId::Named(UDFStatics::ANCHOR, Id));
	return Parameter;
}

template <class Type>
Type* UParamUtil::Setup(FString Name, bool Required, Type* Parameter)
{
	return Setup(FGuid::NewGuid().ToString(), Name, Required, Parameter);
}

template <class Param, typename Value>
Param* UParamUtil::Global(FString Name, bool Required, Value DefaultValue)
{
	return Setup(Name, Required, Param::New(UDFStatics::ANCHOR, DefaultValue));
}

WidgetWithValue* UParamUtil::GetValueWidget(UUserWidget* Outer, UAbstractParameterValue* Value, ParameterType Type)
{
	WidgetWithValue* Widget = nullptr;
	switch (Type)
	{
		case INTEGER:
			{
				Widget = DFUIUtil::MakeWidget<UIntTextBox>(Outer->WidgetTree);
				break;
			}
		case BOOLEAN:
			{
				Widget = DFUIUtil::MakeWidget<UParameterBindingCheckbox>(Outer->WidgetTree);
				break;
			}
		case FLOAT:
			{
				Widget = DFUIUtil::MakeWidget<UFloatTextBox>(Outer->WidgetTree);
				break;
			}
		case COLOR:
			{
				Widget = DFUIUtil::MakeWidget<UFColorTextBox>(Outer->WidgetTree);
				break;
			}
		case ENUM:
			{
				Widget = DFUIUtil::MakeWidget<UParameterBindingComboBox>(Outer->WidgetTree);
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
