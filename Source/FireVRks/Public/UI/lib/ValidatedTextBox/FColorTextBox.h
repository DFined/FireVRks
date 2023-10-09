#pragma once
#include "ValidatedTextBox.h"
#include "FX/Niagara/v2/ParameterValueContext.h"
#include "FX/Niagara/v2/ParameterValue/AbstractParameterValue.h"
#include "FColorTextBox.generated.h"

UCLASS(Blueprintable, BlueprintType)
class FIREVRKS_API UFColorTextBox : public UValidatedTextBox
{
	GENERATED_BODY()
public:
	static bool ValidateColor(FString Value);

	static FRegexPattern PATTERN;
	
	UFColorTextBox(const FObjectInitializer& Initializer) : UValidatedTextBox(Initializer, ValidateColor)
	{
	};

	
	virtual UAbstractParameterValue* GetValue(UParameterValueContext* Context) override;

	virtual FString ValueToString(UAbstractParameterValue* Value) override;
};
