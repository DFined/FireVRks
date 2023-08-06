#include "FX/Niagara/System/SOSSpawnData.h"

SOSSpawnData::~SOSSpawnData()
{
	SafeRelease(SpawnData);
}
