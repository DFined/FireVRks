// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ValidatedTextBox.h"
#include "UI/lib/DFStyleUtil.h"
#include "TimeValidatedTextBox.generated.h"

UCLASS(Blueprintable, BlueprintType)
class FIREVRKS_API UTimeValidatedTextBox : public UValidatedTextBox
{
	GENERATED_BODY()

public:
	static bool ValidateTime(FString Value);
	UTimeValidatedTextBox(const FObjectInitializer& Initializer) : UValidatedTextBox(Initializer, ValidateTime)
	{
		DFStyleUtil::TextBoxStyle(this);
	}
	
	virtual UAbstractParameterValue* GetValue(UParameterValueContext* Context) override;

	virtual FString ValueToString(UAbstractParameterValue* Value) override;

	float GetSeconds();

	virtual void OnChange() override;

	void SetSeconds(float seconds);
};