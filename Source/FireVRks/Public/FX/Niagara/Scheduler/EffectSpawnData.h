#pragma once
#include "FX/Niagara/SystemSettings/InstanceParameter/ParameterValueContext.h"
#include "Util/DFManaged.h"

class UEffectSystem;
/**
 * Data class with all the info needed by the scheduler to spawn/drive the effect
 */
class EffectSpawnData : public DFManaged
{
	UEffectSystem* System;
	ParameterValueContext* Context;
	AActor* SpawnTarget;
	float SpawnIn;
	FVector Offset;
	FVector UpwardsVector;

public:
	EffectSpawnData(
		UEffectSystem* System,
		ParameterValueContext* Context,
		AActor* SpawnTarget,
		float SpawnIn,
		FVector FOffset,
		FVector Velocity = FVector(0),
		bool Managed = false
	)
		: DFManaged(Managed),
		  System(System),
		  Context(Context),
		  SpawnTarget(SpawnTarget),
		  SpawnIn(SpawnIn),
		  Offset(FOffset),
		  UpwardsVector(Velocity)
	{
		Context->Depend();
	}

	UEffectSystem* GetSystem() const
	{
		return System;
	}

	ParameterValueContext* GetContext() const
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

	friend bool operator<(EffectSpawnData& Lhs, EffectSpawnData& RHS)
	{
		return Lhs.SpawnIn < RHS.SpawnIn;
	}

	friend bool operator>(EffectSpawnData& Lhs, EffectSpawnData& RHS)
	{
		return Lhs.SpawnIn > RHS.SpawnIn;
	}

	~EffectSpawnData();
};
