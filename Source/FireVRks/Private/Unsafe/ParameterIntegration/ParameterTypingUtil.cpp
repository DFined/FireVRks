#include "Unsafe/ParameterIntegration/ParameterTypingUtil.h"

#include "FX/Niagara/SystemSettings/Enums/EnumLikeValue.h"
#include "FX/Niagara/SystemSettings/ParameterValues/ParameterValue.h"
#include "UI/DFUIUtil.h"
#include "UI/lib/ValidatedTextBox/FColorTextBox.h"
#include "UI/lib/ValidatedTextBox/FloatTextBox.h"
#include "UI/lib/ValidatedTextBox/IntTextBox.h"
#include "UI/ParameterIntegration/ParameterBindingCheckbox.h"
#include "UI/ParameterIntegration/ParameterBindingComboBox.h"

ParamUtilObject ParameterTypingUtil::INT_PARAM_UTIL_OBJECT = ParamUtilObject(
	[](UWidgetTree* Outer) { return static_cast<ParameterBindingWidget*>(DFUIUtil::MakeWidget<UIntTextBox>(Outer)); },
	[](AbstractParameterValue* Value) { return FString::FromInt(static_cast<ParameterValue<int>*>(Value)->Get()); }
);


ParamUtilObject ParameterTypingUtil::FLOAT_PARAM_UTIL_OBJECT = ParamUtilObject(
	[](UWidgetTree* Outer) { return static_cast<ParameterBindingWidget*>(DFUIUtil::MakeWidget<UFloatTextBox>(Outer)); },
	[](AbstractParameterValue* Value) { return FString::SanitizeFloat(static_cast<ParameterValue<float>*>(Value)->Get()); }
);


ParamUtilObject ParameterTypingUtil::VECTOR_PARAM_UTIL_OBJECT = ParamUtilObject(
	[](UWidgetTree* Outer) { return static_cast<ParameterBindingWidget*>(DFUIUtil::MakeWidget<UFColorTextBox>(Outer)); },
	[](AbstractParameterValue* Value)
	{
		auto Color = static_cast<ParameterValue<FLinearColor>*>(Value)->Get();
		return FString::FromInt(static_cast<int>(Color.R)) + "," + FString::FromInt(static_cast<int>(Color.G)) + "," + FString::FromInt(static_cast<int>(Color.B));
	}
);

ParamUtilObject ParameterTypingUtil::BOOL_PARAM_UTIL_OBJECT = ParamUtilObject(
	[](UWidgetTree* Outer) { return static_cast<ParameterBindingWidget*>(DFUIUtil::MakeWidget<UParameterBindingCheckbox>(Outer)); },
	[](AbstractParameterValue* Value) { return FString::FromInt(static_cast<ParameterValue<int>*>(Value)->Get()); }
);

ParamUtilObject ParameterTypingUtil::ENUM_PARAM_UTIL_OBJECT = ParamUtilObject(
	[](UWidgetTree* Outer) { return static_cast<ParameterBindingWidget*>(DFUIUtil::MakeWidget<UParameterBindingComboBox>(Outer)); },
	[](AbstractParameterValue* Value) { return static_cast<ParameterValue<EnumLikeValue>*>(Value)->Get().Name; }
);

ParamUtilObject* ParameterTypingUtil::GetParamUtil(DFType ParamType)
{
	switch (ParamType)
	{
		case DFType::TYPED_INT_PARAMETER: return &INT_PARAM_UTIL_OBJECT;
		case DFType::TYPED_FLOAT_PARAMETER: return &FLOAT_PARAM_UTIL_OBJECT;
		case DFType::TYPED_VECTOR_PARAMETER: return &VECTOR_PARAM_UTIL_OBJECT;
		case DFType::TYPED_BOOL_PARAMETER: return &BOOL_PARAM_UTIL_OBJECT;
		case DFType::TYPED_ENUM_PARAMETER: return &ENUM_PARAM_UTIL_OBJECT;
		default: return nullptr;
	}
}

template <class ValueType>
ParameterValue<ValueType>* ParameterTypingUtil::ToValue(AbstractParameterValue* Value)
{
	return static_cast<ParameterValue<ValueType>*>(Value);
}
