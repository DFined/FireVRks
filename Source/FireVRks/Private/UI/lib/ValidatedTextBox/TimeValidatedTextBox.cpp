// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/lib/ValidatedTextBox/TimeValidatedTextBox.h"

#include "Util/DFU.h"

bool UTimeValidatedTextBox::ValidateTime(FString Value)
{
	FRegexMatcher IntMatched = FRegexMatcher(FRegexPattern(TEXT("[0-5][0-9]:[0-5][0-9]\\.[0-9][0-9]")), Value);
	IntMatched.FindNext();
	int start = IntMatched.GetMatchBeginning();
	int end = IntMatched.GetMatchEnding();
	return (end - start) == Value.Len();
}

UAbstractParameterValue* UTimeValidatedTextBox::GetValue(UObject* Outer)
{
	return nullptr;
}

FString UTimeValidatedTextBox::ValueToString(UAbstractParameterValue* Value)
{
	return "";
}

float UTimeValidatedTextBox::GetSeconds()
{
	FString Minutes;
	FString Seconds;
	FString DeciSeconds;

	FString Tail;
	this->GetText().ToString().Split(":", &Minutes, &Tail);
	Tail.Split(".", &Seconds, &DeciSeconds);
	return FCString::Atof(*Minutes) * 60 + FCString::Atof(*Seconds) + FCString::Atof(*DeciSeconds) / 100;
}

void UTimeValidatedTextBox::OnChange()
{
}

void UTimeValidatedTextBox::SetSeconds(float SecondsIn)
{
	this->SetText(FText::FromString(DFU::SecondsToTimeCode(SecondsIn)));
	this->PrevText = DFU::SecondsToTimeCode(SecondsIn);
}
