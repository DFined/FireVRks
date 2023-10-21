// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FX/Niagara/v2/ParameterValueContext.h"
#include "UObject/Object.h"
#include "DisplayLaunchSegment.generated.h"

/**
 * A set of launch settings to be processed at a single instance
 */
UCLASS()
class FIREVRKS_API UDisplayLaunchSegment : public UObject
{
	GENERATED_BODY()
	
	float Time;

	UPROPERTY()
	TArray<UParameterValueContext*> LaunchSettings;

public:
	TArray<UParameterValueContext*>* GetLaunchSettings();

	float GetTime() const
	{
		return Time;
	}

	void SetTime(float fTime)
	{
		this->Time = fTime;
	}

	static UDisplayLaunchSegment* New(UObject* Outer);
};
