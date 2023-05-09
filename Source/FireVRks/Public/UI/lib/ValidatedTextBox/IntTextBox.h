#pragma once
#include "ValidatedTextBox.h"
#include "IntTextBox.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UIntTextBox : public UValidatedTextBox
{
	GENERATED_BODY()
public:
	static bool ValidateInt(FString Value);
	UIntTextBox(const FObjectInitializer& Initializer) : UValidatedTextBox(Initializer, ValidateInt)
	{
	};

	
	virtual AbstractParameterValue* GetValue() override;

};
