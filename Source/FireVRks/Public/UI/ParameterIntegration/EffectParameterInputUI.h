#pragma once
#include "ParameterInputUI.h"
#include "FX/Niagara/System/EffectSystem.h"
#include "FX/Niagara/System/SystemAndContext.h"
#include "FX/Niagara/SystemSettings/InstanceParameter/MapParameterValueContext.h"
#include "EffectParameterInputUI.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UEffectParameterInputUI : public UParameterInputUI
{
	GENERATED_BODY()

	MapParameterValueContext* Context = nullptr;

	UPROPERTY()
	UEffectSystem* System;
	
public:
	UEffectParameterInputUI();

	void SetSystem(UEffectSystem* FSystem)
	{
		this->System = FSystem;
		this->SetProvider(FSystem);
	}

	//TODO remove this
	UFUNCTION(BlueprintCallable)
	void SpawnSystem(AActor* Target);


	UFUNCTION(BlueprintCallable)
	USystemAndContext* GetSpawnObject();
	
};

