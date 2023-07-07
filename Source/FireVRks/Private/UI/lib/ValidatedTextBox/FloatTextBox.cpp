#include "UI/lib/ValidatedTextBox/FloatTextBox.h"

#include "FX/Niagara/SystemSettings/FormalParameter/FormalParameter.h"

bool UFloatTextBox::ValidateFloat(FString Value) {
	FRegexMatcher IntMatched = FRegexMatcher(FRegexPattern(TEXT("(0|[1-9][0-9]*)(\\.[0-9]*)?")), Value);
	IntMatched.FindNext();
	int start = IntMatched.GetMatchBeginning();
	int end = IntMatched.GetMatchEnding();
	return (end - start) == Value.Len();
}

AbstractParameterValue* UFloatTextBox::GetValue()
{
	FString str = this->GetText().ToString();
	return new ParameterValue(FCString::Atof(*str), DFType::TYPED_FLOAT_PARAMETER, false);
}
