// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ValidatedTextBox.h"
#include "DFUI/DFStyleUtil.h"
#include "TimeValidatedTextBox.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeChanged, float, NewTime);

UCLASS(Blueprintable, BlueprintType)
class FIREVRKS_API UTimeValidatedTextBox : public UValidatedTextBox
{
	GENERATED_BODY()

	FOnTimeChanged OnTimeChanged = FOnTimeChanged();
	
public:
	static bool ValidateTime(FString Value);
	UTimeValidatedTextBox(const FObjectInitializer& Initializer) : UValidatedTextBox(Initializer, ValidateTime)
	{
		DFStyleUtil::TextBoxStyle(this);
	}
	
	virtual UAbstractParameterValue* GetValue(UObject* Outer) override;

	virtual FString ValueToString(UAbstractParameterValue* Value) override;

	float GetSeconds();

	virtual void OnChange() override;

	void SetSeconds(float seconds);

	FOnTimeChanged& GetOnTimeChanged();
};