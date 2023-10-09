#pragma once
#include "FX/Niagara/v2/ParameterValueContext.h"
#include "EffectSpawnData.generated.h"

class UEffectSystem;
/**
 * Data class with all the info needed by the scheduler to spawn/drive the effect
 */
UCLASS()
class FIREVRKS_API UEffectSpawnData : public UObject 
{
	GENERATED_BODY()
	
	UPROPERTY()
	UEffectSystem* System;
	UPROPERTY()
	UParameterValueContext* Context;
	UPROPERTY()
	AActor* SpawnTarget;
	
	float SpawnIn;
	FVector Offset;
	FVector UpwardsVector;

public:
	UEffectSystem* GetSystem() const
	{
		return System;
	}

	UParameterValueContext* GetContext() const
	{
		return Context;
	}

	AActor* GetSpawnTarget() const
	{
		return SpawnTarget;
	}

	float GetSpawnIn() const
	{
		return SpawnIn;
	}

	void SetSpawnIn(float FSpawnIn)
	{
		this->SpawnIn = FSpawnIn;
	}

	bool IsValid()
	{
		return System && SpawnTarget && Context;
	}

	

	FVector GetOffset() const
	{
		return Offset;
	}

	FVector GetUpwards() const
	{
		return UpwardsVector;
	}

	friend bool operator<(UEffectSpawnData& Lhs, UEffectSpawnData& RHS)
	{
		return Lhs.SpawnIn < RHS.SpawnIn;
	}

	friend bool operator>(UEffectSpawnData& Lhs, UEffectSpawnData& RHS)
	{
		return Lhs.SpawnIn > RHS.SpawnIn;
	}

	static UEffectSpawnData* New(
		UObject* Outer, UEffectSystem* System, UParameterValueContext* Context, AActor* Target, float SpawnDelay, FVector Offset, FVector UpwardsDirection);
};