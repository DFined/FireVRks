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

public:
	UFUNCTION(BlueprintCallable)
	void Tick(bool IsTest, float DeltaSeconds);

	void SpawnEffect(ULaunchSettings* Data);

	UFUNCTION(BlueprintCallable)
	void Enqueue(bool IsTest, ULaunchSettings* Data);

	static UEffectSpawnCoordinator* New();
};
