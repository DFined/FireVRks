#pragma once
#include "ValidatedTextBox.h"
#include "FX/Niagara/v2/ParameterValueContext.h"
#include "FX/Niagara/v2/ParameterValue/AbstractParameterValue.h"
#include "FloatTextBox.generated.h"

UCLASS(Blueprintable, BlueprintType)
class FIREVRKS_API UFloatTextBox : public UValidatedTextBox
{
	GENERATED_BODY()
public:
	static bool ValidateFloat(FString Value);
	UFloatTextBox(const FObjectInitializer& Initializer) : UValidatedTextBox(Initializer, ValidateFloat)
	{
	};

	
	virtual UAbstractParameterValue* GetValue(UObject* Outer) override;

	virtual FString ValueToString(UAbstractParameterValue* Value) override;
};
