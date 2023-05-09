#pragma once
#include "ValidatedTextBox.h"
#include "FColorTextBox.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UFColorTextBox : public UValidatedTextBox
{
	GENERATED_BODY()
public:
	static bool ValidateColor(FString Value);
	UFColorTextBox(const FObjectInitializer& Initializer) : UValidatedTextBox(Initializer, ValidateColor)
	{
	};

	
	virtual AbstractParameterValue* GetValue() override;

};
