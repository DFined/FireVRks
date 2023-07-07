#pragma once
#include "FX/Niagara/Scheduler/EffectSpawnData.h"

class SOSSpawnData : public DFManaged
{
public:
	EffectSpawnData* SpawnData;

	float SpawnIn;
	bool FromEnd;
	bool RecurringInterval;

	int SpawnCount;

	SOSSpawnData(EffectSpawnData* SpawnData, float FSpawnIn, bool bFromEnd, bool bRecurringInterval, int SosSpawnCount) : DFManaged(false),
		SpawnData(SpawnData),
		FromEnd(bFromEnd),
		RecurringInterval(bRecurringInterval),
		SpawnIn(FSpawnIn),
		SpawnCount(SosSpawnCount)
	{
		SpawnData->Depend();
	}

	friend bool operator<(const SOSSpawnData& Lhs, const SOSSpawnData& RHS)
	{
		return Lhs.SpawnIn < RHS.SpawnIn;
	}

	friend bool operator>(SOSSpawnData& Lhs, SOSSpawnData& RHS)
	{
		return Lhs.SpawnIn > RHS.SpawnIn;
	}

	~SOSSpawnData();

	float GetSpawnDelay()
	{
		return SpawnIn;
	};

	int GetSpawnCount() const
	{
		return SpawnCount;
	}
};
