#include "UI/lib/ValidatedTextBox/FColorTextBox.h"

#include "FX/Niagara/SystemSettings/FormalParameter/FormalParameter.h"

FRegexPattern UFColorTextBox::PATTERN = FRegexPattern(TEXT("[1-2]?[0-9]?[0-9]?"));

bool UFColorTextBox::ValidateColor(FString Value)
{
	TArray<FString> Parts = TArray<FString>();
	FString delim = ",";
	Value.ParseIntoArray(Parts, *delim);
	if(Parts.Num() != 3)
	{
		return false;
	}
	for(FString Part : Parts)
	{
		FRegexMatcher IntMatched = FRegexMatcher(
				PATTERN,
				Part
			);
		IntMatched.FindNext();
		int start = IntMatched.GetMatchBeginning();
		int end = IntMatched.GetMatchEnding();
		if((end - start) != Part.Len())
		{
			return false;
		}
	}
	return true;
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
