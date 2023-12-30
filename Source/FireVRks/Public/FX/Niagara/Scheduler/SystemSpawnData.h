// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FX/Niagara/v2/ParameterValueContext.h"
#include "UObject/Object.h"
#include "SystemSpawnData.generated.h"

/**
 * 
 */
UCLASS()
class FIREVRKS_API USystemSpawnData : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	UParameterValueContext* Context;

	UPROPERTY()
	UObject* WorldObject;

	FVector Location;
	FVector UpwardVector;

public:
	UParameterValueContext* GetContext() const
	{
		return Context;
	}

	UObject* GetWorldObject() const
	{
		return WorldObject;
	}

	FVector& GetLocation() 
	{
		return Location;
	}

	FVector& GetUpwardVector()
	{
		return UpwardVector;
	}

	static USystemSpawnData* New(UObject* Outer, UParameterValueContext* bContext, FVector Location, FVector bUpwardsVector)
	{
		auto Data = NewObject<USystemSpawnData>(Outer, StaticClass());
		Data->WorldObject = Outer;
		Data->Context = bContext;
		Data->Location = Location;
		Data->UpwardVector = bUpwardsVector;
		return Data;
	}
};
