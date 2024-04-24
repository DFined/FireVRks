// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericLauncherArray.h"
#include "UObject/Object.h"
#include "Util/DFU.h"
#include "LauncherData.generated.h"

class AGenericFireworkLauncher;
/**
 * A non-actor data instance for a launcher that can be persisted between levels
 */
UCLASS(BlueprintType)
class FIREVRKS_API ULauncherData : public UObject
{
	GENERATED_BODY()

	FVector Location;
	FRotator Rotation;

	UPROPERTY()
	AGenericFireworkLauncher* Launcher;

public:
	TSharedPtr<FJsonObject> ToJson() const;
	static void FromJson(TSharedPtr<FJsonObject> Json, FString ArrayName, UObject* WCO);
	
	AGenericFireworkLauncher* GetActor();

	void Materialize(UWorld* World);

	DF_NEW2(ULauncherData, FVector, Location, FRotator, Rotation);

	FVector& GetLocation();
	void SetLocation(const FVector& Location);
	FRotator& GetRotation();
	void SetRotation(const FRotator& Rotation);
};
