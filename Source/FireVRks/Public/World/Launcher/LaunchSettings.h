#pragma once
#include "FX/Niagara/v2/System/EffectSystem.h"
#include "LaunchSettings.generated.h"

UCLASS()
class FIREVRKS_API ULaunchSettings : public UObject
{
	GENERATED_BODY()
	
	UPROPERTY()
	UEffectSystem* System;

	UPROPERTY()
	UParameterValueContext* Context;

	float ShellLifetime;
	float ShellVelocity;
public:

	static ULaunchSettings* Make(UObject* Outer, UEffectSystem* FSystem, UParameterValueContext* FContext, float FShellLifetime, float FShellVelocity)
	{
		auto Settings = NewObject<ULaunchSettings>(Outer, StaticClass());
		Settings->System = FSystem;
		Settings->Context = FContext;
		Settings->ShellLifetime = FShellLifetime;
		Settings->ShellVelocity = FShellVelocity;
		return Settings;
	}

	UEffectSystem* GetSystem() const
	{
		return System;
	}

	UParameterValueContext* GetContext() const
	{
		return Context;
	}

	float GetShellLifetime() const
	{
		return ShellLifetime;
	}

	float GetShellVelocity() const
	{
		return ShellVelocity;
	}
};
