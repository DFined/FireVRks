#include "UI/lib/ValidatedTextBox/IntTextBox.h"

#include "FX/Niagara/v2/ParameterValueContext.h"
#include "FX/Niagara/v2/ParamUtil.h"
#include "FX/Niagara/v2/ParameterValue/IntParameterValue.h"

bool UIntTextBox::ValidateInt(FString Value) {
	FRegexMatcher IntMatched = FRegexMatcher(FRegexPattern(TEXT("\\-?(0|[1-9][0-9]*)")), Value);
	IntMatched.FindNext();
	int start = IntMatched.GetMatchBeginning();
	int end = IntMatched.GetMatchEnding();
	return (end - start) == Value.Len();
}

UAbstractParameterValue* UIntTextBox::GetValue(UObject* Outer)
{
	FString str = this->GetText().ToString();
	return UIntParameterValue::New(Outer, FCString::Atoi(*str));
}

FString UIntTextBox::ValueToString(UAbstractParameterValue* Value)
{
	return FString::FromInt(UParamUtil::GetTypedValue<UIntParameterValue, int>(Value));
}
