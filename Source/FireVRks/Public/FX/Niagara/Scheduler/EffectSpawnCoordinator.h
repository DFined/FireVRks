// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LaunchSettings.h"
#include "UObject/Object.h"
#include "EffectSpawnCoordinator.generated.h"

UCLASS()
class FIREVRKS_API UEffectSpawnCoordinator : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<ULaunchSettings*> TestQueue;
	UPROPERTY()
	TArray<ULaunchSettings*> DisplayQueue;

	float CurrentPlaybackPosition = 0;
	int NumSkip = 0;

public:
	UFUNCTION(BlueprintCallable)
	void TickTesting(float DeltaSeconds);
	UFUNCTION(BlueprintCallable)
	void TickDisplay(float DeltaSeconds);

	void SpawnEffect(ULaunchSettings* Data);

	UFUNCTION(BlueprintCallable)
	void EnqueueTest(ULaunchSettings* Data);
	void EnqueueDisplay(ULaunchSettings* Data);

	UFUNCTION(BlueprintCallable)
	void Seek(float Location);
	void Reset();

	static UEffectSpawnCoordinator* New();
};
