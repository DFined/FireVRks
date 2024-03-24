#include "FX/Niagara/Scheduler/LaunchSettings.h"

ULaunchSettings* ULaunchSettings::Make(UObject* Outer, UEffectSystem* fSystem, UParameterValueContext* fContext, AActor* bSpawnTarget, float fDelay,
	float fLifetime, float fVelocity, int Roll)
{
	auto Data = NewObject<ULaunchSettings>(Outer, StaticClass());
	Data->System = fSystem;
	Data->Context = fContext;
	Data->SpawnTarget = bSpawnTarget;
	Data->SpawnIn = fDelay;
	Data->ShellLifetime = fLifetime;
	Data->ShellVelocity = fVelocity;
	Data->DegressRoll = Roll;
	
	return Data;
}

int ULaunchSettings::GetDegressRoll()
{
	return DegressRoll;
}
