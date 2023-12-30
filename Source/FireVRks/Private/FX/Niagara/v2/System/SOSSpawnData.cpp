#include "FX/Niagara/v2/System/SOSSpawnData.h"

SOSSpawnData::SOSSpawnData(ULaunchSettings* SpawnData, float FSpawnIn, bool bFromEnd, bool bRecurringInterval, int SosSpawnCount):
	SpawnData(SpawnData),
	FromEnd(bFromEnd),
	RecurringInterval(bRecurringInterval),
	SpawnIn(FSpawnIn),
	SpawnCount(SosSpawnCount)
{
}

SOSSpawnData::~SOSSpawnData()
{
}

float SOSSpawnData::GetSpawnDelay()
{
	return SpawnIn;
}

int SOSSpawnData::GetSpawnCount() const
{
	return SpawnCount;
}

bool operator<(const SOSSpawnData& Lhs, const SOSSpawnData& RHS)
{
	return Lhs.SpawnIn < RHS.SpawnIn;
}

bool operator>(SOSSpawnData& Lhs, SOSSpawnData& RHS)
{
	return Lhs.SpawnIn > RHS.SpawnIn;
}
