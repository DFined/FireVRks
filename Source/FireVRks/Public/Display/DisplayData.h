// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DisplayLaunchSegment.h"
#include "UObject/Object.h"
#include "DisplayData.generated.h"

/**
 * All the necessary data to store, load, process an playback an entire display
 */
UCLASS()
class FIREVRKS_API UDisplayData : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<UDisplayLaunchSegment*> LaunchSegments;

	FString TrackPath;

public:
	TArray<UDisplayLaunchSegment*>* GetLaunchSegments();

	void Remove(UDisplayLaunchSegment* Segment)
	{
		LaunchSegments.Remove(Segment);
	}

	static UDisplayData* New(UObject* Outer);
};
