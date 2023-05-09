#pragma once
#include "ValidatedTextBox.h"
#include "FloatTextBox.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UFloatTextBox : public UValidatedTextBox
{
	GENERATED_BODY()
public:
	static bool ValidateFloat(FString Value);
	UFloatTextBox(const FObjectInitializer& Initializer) : UValidatedTextBox(Initializer, ValidateFloat)
	{
	};

	
	virtual AbstractParameterValue* GetValue() override;

};
