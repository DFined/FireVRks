#include "FX/Niagara/Scheduler/EffectSpawnData.h"

UEffectSpawnData* UEffectSpawnData::New(
	UObject* Outer, UEffectSystem* System, UParameterValueContext* Context, AActor* Target, float SpawnDelay, FVector Offset, FVector UpwardsDirection
)
{
	auto Data = NewObject<UEffectSpawnData>(Outer, StaticClass());
	Data->System = System;
	Data->Context = Context;
	Data->SpawnTarget = Target;
	Data->SpawnIn = SpawnDelay;
	Data->Offset = Offset;
	Data->UpwardsVector = UpwardsDirection;
	return Data;
}
