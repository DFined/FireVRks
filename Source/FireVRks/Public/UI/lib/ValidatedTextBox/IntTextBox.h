#pragma once
#include "ValidatedTextBox.h"
#include "FX/Niagara/v2/ParameterValueContext.h"
#include "FX/Niagara/v2/ParameterValue/AbstractParameterValue.h"
#include "IntTextBox.generated.h"

UCLASS(Blueprintable, BlueprintType)
class FIREVRKS_API UIntTextBox : public UValidatedTextBox
{
	GENERATED_BODY()
public:
	static bool ValidateInt(FString Value);
	UIntTextBox(const FObjectInitializer& Initializer) : UValidatedTextBox(Initializer, ValidateInt)
	{
	};
	
	virtual UAbstractParameterValue* GetValue(UParameterValueContext* Context) override;

	virtual FString ValueToString(UAbstractParameterValue* Value) override;
};
