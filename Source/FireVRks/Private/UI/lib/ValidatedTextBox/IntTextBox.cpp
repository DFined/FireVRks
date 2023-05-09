#include "UI/lib/ValidatedTextBox/IntTextBox.h"

#include "FX/Niagara/SystemSettings/FormalParameter/FormalParameter.h"

bool UIntTextBox::ValidateInt(FString Value) {
	FRegexMatcher IntMatched = FRegexMatcher(FRegexPattern(TEXT("0|[1-9][0-9]*")), Value);
	IntMatched.FindNext();
	int start = IntMatched.GetMatchBeginning();
	int end = IntMatched.GetMatchEnding();
	return (end - start) == Value.Len();
}

AbstractParameterValue* UIntTextBox::GetValue()
{
	FString str = this->GetText().ToString();
	return new ParameterValue(FCString::Atoi(*str), DFType::TYPED_INT_PARAMETER, false);
}
