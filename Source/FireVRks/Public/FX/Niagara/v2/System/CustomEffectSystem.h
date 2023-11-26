// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectSystem.h"
#include "SystemParameterBindings.h"
#include "CustomEffectSystem.generated.h"

/**
 * 
 */
UCLASS()
class FIREVRKS_API UCustomEffectSystem : public UEffectSystem
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<UDFId*, USystemParameterBindings*> SubsystemConfig;

	UPROPERTY()
	TArray<UAbstractFormalParameter*> OuterParameters;

public:
	virtual void SpawnSystem(USystemSpawnData* Data) override;
};
