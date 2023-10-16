#pragma once
#include "FX/Niagara/v2/ParameterValueContext.h"
#include "FX/Niagara/v2/System/EffectSystem.h"
#include "LaunchSettings.generated.h"

class UEffectSystem;
/**
 * Data class with all the info needed by the scheduler to spawn/drive the effect
 */
UCLASS()
class FIREVRKS_API ULaunchSettings : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	UEffectSystem* System;
	UPROPERTY()
	UParameterValueContext* Context;
	UPROPERTY()
	AActor* SpawnTarget;

	float SpawnIn;

	float ShellLifetime;
	float ShellVelocity;

	bool Used = false;

public:
	static ULaunchSettings* Make(
		UObject* Outer, UEffectSystem* fSystem, UParameterValueContext* fContext, AActor* SpawnTarget, float fDelay, float fLifetime, float fVelocity
	);

	void SetSpawnTarget(AActor* fSpawnTarget)
	{
		this->SpawnTarget = fSpawnTarget;
	}

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


	float GetShellLifetime() const
	{
		return ShellLifetime;
	}

	float GetShellVelocity() const
	{
		return ShellVelocity;
	}

	friend bool operator<(ULaunchSettings& Lhs, ULaunchSettings& RHS)
	{
		return Lhs.SpawnIn < RHS.SpawnIn;
	}

	friend bool operator>(ULaunchSettings& Lhs, ULaunchSettings& RHS)
	{
		return Lhs.SpawnIn > RHS.SpawnIn;
	}

};
