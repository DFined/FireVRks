#include "UI/lib/ValidatedTextBox/FloatTextBox.h"

#include "FX/Niagara/v2/ParameterValueContext.h"
#include "FX/Niagara/v2/ParamUtil.h"
#include "FX/Niagara/v2/ParameterValue/AbstractParameterValue.h"
#include "FX/Niagara/v2/ParameterValue/FloatParameterValue.h"

bool UFloatTextBox::ValidateFloat(FString Value) {
	FRegexMatcher IntMatched = FRegexMatcher(FRegexPattern(TEXT("(0|[1-9][0-9]*)(\\.[0-9]*)?")), Value);
	IntMatched.FindNext();
	int start = IntMatched.GetMatchBeginning();
	int end = IntMatched.GetMatchEnding();
	return (end - start) == Value.Len();
}

UAbstractParameterValue* UFloatTextBox::GetValue(UParameterValueContext* Context)
{
	FString str = this->GetText().ToString();
	return UFloatParameterValue::New(Context, FCString::Atof(*str));
}

FString UFloatTextBox::ValueToString(UAbstractParameterValue* Value)
{
	return FString::SanitizeFloat(UParamUtil::GetTypedValue<UFloatParameterValue, float>(Value));
}
