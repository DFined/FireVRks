#include "FX/Niagara/Scheduler/EffectSpawnData.h"

EffectSpawnData::~EffectSpawnData()
{
	SafeRelease(Context);
}
