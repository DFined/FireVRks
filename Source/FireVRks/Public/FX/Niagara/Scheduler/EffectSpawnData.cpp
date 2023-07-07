#include "EffectSpawnData.h"

EffectSpawnData::~EffectSpawnData()
{
	SafeRelease(Context);
}
