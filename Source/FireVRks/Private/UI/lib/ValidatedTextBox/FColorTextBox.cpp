#include "UI/lib/ValidatedTextBox/FColorTextBox.h"

#include "FX/Niagara/SystemSettings/FormalParameter/FormalParameter.h"

bool UFColorTextBox::ValidateColor(FString Value)
{
	FRegexMatcher IntMatched = FRegexMatcher(
		FRegexPattern(
			TEXT("([0-9]|[1-9][0-9]|[1-2][0-9][0-9]),([0-9]|[1-9][0-9]|[1-2][0-9][0-9]),([0-9]|[1-9][0-9]|[1-2][0-9][0-9])")
		),
		Value
	);
	IntMatched.FindNext();
	int start = IntMatched.GetMatchBeginning();
	int end = IntMatched.GetMatchEnding();
	return (end - start) == Value.Len();
}

AbstractParameterValue* UFColorTextBox::GetValue()
{
	FString Str = this->GetText().ToString();
	TArray<FString> Parts = TArray<FString>();
	FString delim = ",";
	Str.ParseIntoArray(Parts, *delim);
	return new ParameterValue(FLinearColor(FCString::Atof(*Parts[0]), FCString::Atof(*Parts[1]), FCString::Atof(*Parts[2]), 255),
	                          DFType::TYPED_VECTOR_PARAMETER, false);
}
