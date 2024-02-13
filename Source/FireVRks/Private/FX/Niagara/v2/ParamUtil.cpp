#include "FX/Niagara/v2/ParamUtil.h"

#include "FX/Niagara/v2/FormalParameter/BoolFormalParameter.h"
#include "FX/Niagara/v2/FormalParameter/ColorFormalParameter.h"
#include "FX/Niagara/v2/FormalParameter/FloatFormalParameter.h"
#include "FX/Niagara/v2/FormalParameter/IntFormalParameter.h"
#include "FX/Niagara/v2/ParameterValue/IntParameterValue.h"
#include "DFUI/DFUI.h"
#include "UI/lib/ParameterBindingCheckbox.h"
#include "UI/lib/ParameterBindingComboBox.h"
#include "UI/lib/ValidatedTextBox/FColorTextBox.h"
#include "UI/lib/ValidatedTextBox/FloatTextBox.h"
#include "UI/lib/ValidatedTextBox/IntTextBox.h"
#include "UI/ParameterIntegration/v2/ArraySelectorComboBox.h"
#include "UI/ParameterIntegration/v2/ParameterBindingWidget.h"

WidgetWithValue* UParamUtil::GetValueWidget(UUserWidget* Outer, ParameterType Type)
{
	WidgetWithValue* Widget = nullptr;
	switch (Type)
	{
	case INTEGER:
		{
			Widget = DFUI::MakeWidget<UIntTextBox>(Outer);
			break;
		}
	case BOOLEAN:
		{
			Widget = DFUI::MakeWidget<UParameterBindingCheckbox>(Outer);
			break;
		}
	case FLOAT:
		{
			Widget = DFUI::MakeWidget<UFloatTextBox>(Outer);
			break;
		}
	case COLOR:
		{
			Widget = DFUI::MakeWidget<UFColorTextBox>(Outer);
			break;
		}
	case ENUM:
		{
			Widget = DFUI::MakeWidget<UParameterBindingComboBox>(Outer);
			break;
		}
	case ARRAY_SELECTOR:
		{
			Widget = DFUI::MakeWidget<UArraySelectorComboBox>(Outer);
			break;
		}
	}
	return Widget;
}

void UParamUtil::WriteContainerToContext(UPanelWidget* Container, UParameterValueContext* Context)
{
	for (UWidget* Child : Container->GetAllChildren())
	{
		if (auto Widget = Cast<UParameterBindingWidget>(Child))
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

UAbstractParameterValue* UParamUtil::ValueFromJson(TSharedPtr<FJsonObject> Json, UObject* Outer)
{
	auto TypeName = Json->GetStringField("Type");
	switch (TypeFromName(TypeName))
	{
	case INTEGER: return UIntParameterValue::New(Outer, Json->GetIntegerField("Value"));
	case FLOAT: return UIntParameterValue::New(Outer, Json->GetNumberField("Value"));
	case COLOR: return UColorParameterValue::New(
			Outer,
			FLinearColor(Json->GetIntegerField("R"), Json->GetIntegerField("G"), Json->GetIntegerField("B"))
		);
	case BOOLEAN: return UBoolParameterValue::New(Outer, Json->GetBoolField("Value"));
	default: throw std::runtime_error("Attempting to deserialize forbidden type");
	}
}

