#include "FX/Niagara/Scheduler/LaunchSettings.h"

ULaunchSettings* ULaunchSettings::Make(UObject* Outer, UEffectSystem* fSystem, UParameterValueContext* fContext, AActor* SpawnTarget, float fDelay,
	float fLifetime, float fVelocity)
{
	auto Data = NewObject<ULaunchSettings>(Outer, StaticClass());
	Data->System = fSystem;
	Data->Context = fContext;
	Data->SpawnTarget = SpawnTarget;
	Data->SpawnIn = fDelay;
	Data->ShellLifetime = fLifetime;
	Data->ShellVelocity = fVelocity;
	return Data;
}
