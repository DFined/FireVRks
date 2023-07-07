#include "SOSSpawnData.h"

SOSSpawnData::~SOSSpawnData()
{
	SafeRelease(SpawnData);
}
