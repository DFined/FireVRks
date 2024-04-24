// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DisplayManager.h"
#include "UObject/Object.h"
#include "DisplayData.generated.h"

class UDisplayLaunchSegment;
/**
 * All the necessary data to store, load, process an playback an entire display
 */
UCLASS()
class FIREVRKS_API UDisplayData : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<UDisplayLaunchSegment*> LaunchSegments;

	FString DisplayName;
	FString Author;
	FString TrackPath;

public:
	TArray<UDisplayLaunchSegment*>& GetLaunchSegments();

	void Remove(UDisplayLaunchSegment* Segment)
	{
		LaunchSegments.Remove(Segment);
	}

	static UDisplayData* FromJson(UObject* Outer, TSharedPtr<FJsonObject> JsonObject);

	static UDisplayData* New(UObject* Outer);

	TSharedPtr<FJsonObject> ToJson();

	void SetAuthor(const FString& Author);
	void SetTrackPath(const FString& TrackPath);

	FString& GetDisplayName();
	void SetDisplayName(const FString DisplayName);
};
