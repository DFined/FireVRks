#pragma once
#include "FX/Niagara/Scheduler/LaunchSettings.h"

class SOSSpawnData
{
public:
	ULaunchSettings* SpawnData;

	float SpawnIn;
	bool FromEnd;
	bool RecurringInterval;

	int SpawnCount;

	SOSSpawnData(ULaunchSettings* SpawnData, float FSpawnIn, bool bFromEnd, bool bRecurringInterval, int SosSpawnCount);

	friend bool operator<(const SOSSpawnData& Lhs, const SOSSpawnData& RHS);

	friend bool operator>(SOSSpawnData& Lhs, SOSSpawnData& RHS);

	~SOSSpawnData();

	float GetSpawnDelay();

	int GetSpawnCount() const;
};
