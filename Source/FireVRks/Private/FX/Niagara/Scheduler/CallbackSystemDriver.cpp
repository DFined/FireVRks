#include "FX/Niagara/Scheduler/CallbackSystemDriver.h"
#include "FX/Niagara/Scheduler/CallbackSystemDriver.h"

#include "FX/Niagara/Scheduler/EffectSystemScheduler.h"
#include "NiagaraComponent.h"
#include "NiagaraDataInterfaceArrayFunctionLibrary.h"
#include "FX/Niagara/System/EffectSystemManager.h"
#include "Util/DFStatics.h"


void ACallbackSystemDriver::GetTimingsArray(TArray<float>& Array, bool backwards)
{
	for (int i = 0; i < ParticleCount; i++)
	{
		TArray<SOSSpawnData*>& SpawnTime = (backwards ? BackwardsSpawnTimes : ForwardsSpawnTimes)[i];
		TArray<int>& AckArray = (backwards ? BackwardsAcks : ForwardsAcks);
		if (AckArray[i] < SpawnTime.Num())
		{
			Array.Add(SpawnTime[AckArray[i]]->SpawnIn);
		}
	}
}

void ACallbackSystemDriver::ReceiveParticleData_Implementation(const TArray<FBasicParticleData>& Data, UNiagaraSystem* NiagaraSystem,
                                                               const FVector& SimulationPositionOffset)
{
	for (const FBasicParticleData& BasicParticleData : Data)
	{
		float Size = BasicParticleData.Size;
		bool Backwards = Size < 0;
		int Num = FMath::Abs(static_cast<int>(Size)) -1;
		TArray<int>& AckArray = (Backwards ? BackwardsAcks : ForwardsAcks);
		int AckNum = AckArray[Num];
		const TArray<TArray<SOSSpawnData*>>& SpawnDataArray = Backwards ? BackwardsSpawnTimes : ForwardsSpawnTimes;
		SOSSpawnData* SpawnData = SpawnDataArray[Num][AckNum];
		FVector Velocity = BasicParticleData.Velocity;
		Velocity.Normalize();
		for (int j = 0; j < SpawnData->SpawnCount; ++j)
		{
			UDFStatics::EFFECT_SYSTEM_SCHEDULER->SpawnNow(
				SpawnData->SpawnData->GetSystem(), this, BasicParticleData.Position, Velocity, SpawnData->SpawnData->GetContext()
			);
		}

		if (AckNum + 1 < SpawnDataArray[Num].Num())
		{
			AckArray[Num] = ++AckNum;
			// Seems to not work in the engine atm, so, unfortunately, have to set whole array every time 
			// UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayInt32Value(System, Backwards ? "BackwardsAcks" : "ForwardsAcks", Num, AckNum, true);
			// UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayFloatValue(
			// 	System, Backwards ? "BackwardsCallbackPoints" : "ForwardsCallbackPoints", Num, SpawnDataArray[Num][AckNum]->GetSpawnDelay(), true
			// );
		}
	}
	TArray<float> ForwardsTimings = TArray<float>();
	TArray<float> BackwardsTimings = TArray<float>();
	GetTimingsArray(ForwardsTimings, false);
	GetTimingsArray(BackwardsTimings, true);

	UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayInt32(System, "ForwardsAcks", ForwardsAcks);
	UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayInt32(System, "BackwardsAcks", BackwardsAcks);
	UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayFloat(System, "ForwardsCallbackPoints", ForwardsTimings);
	UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayFloat(System, "BackwardsCallbackPoints", BackwardsTimings);
}


void ACallbackSystemDriver::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!System->IsActive())
	{
		for (TArray<SOSSpawnData*> ForwardsSpawnTime : ForwardsSpawnTimes)
		{
			for (auto SpawnTime : ForwardsSpawnTime)
			{
				DFManaged::SafeRelease(SpawnTime);
			}
		}

		for (TArray<SOSSpawnData*> BackwardsSpawnTime : BackwardsSpawnTimes)
		{
			for (SOSSpawnData* SpawnTime : BackwardsSpawnTime)
			{
				DFManaged::SafeRelease(SpawnTime);
			}
		}
		this->Destroy();
	}
}

void ACallbackSystemDriver::Init(int ParentParticleCount, float maxLifetime, UNiagaraComponent* BSystem)
{
	this->System = BSystem;
	this->ParticleCount = ParentParticleCount;
	this->MaxLifetime = maxLifetime;
	ForwardsSpawnTimes = TArray<TArray<SOSSpawnData*>>();
	BackwardsSpawnTimes = TArray<TArray<SOSSpawnData*>>();
	ForwardsAcks = TArray<int>();
	BackwardsAcks = TArray<int>();
	for (int i = 0; i < ParentParticleCount; ++i)
	{
		ForwardsSpawnTimes.Add(TArray<SOSSpawnData*>());
		BackwardsSpawnTimes.Add(TArray<SOSSpawnData*>());
		ForwardsAcks.Add(0);
		BackwardsAcks.Add(0);
	}
}

void ACallbackSystemDriver::AddSpawnInfo(EffectSpawnData* Data, float MinSpawnIn, float MaxSpawnIn, int EffectCount, EnumLikeValue* DelayType, int MaxEffects)
{
	for (int i = 0; i < ParticleCount; ++i)
	{
		if (DelayType == &EnumLikeValue::SOS_DELAY_AT_REGULAR_INTERVAL)
		{
			int j = 0;
			float SpawnTime = FMath::RandRange(MinSpawnIn, MaxSpawnIn);
			while (SpawnTime < MaxLifetime && j < MaxEffects)
			{
				auto SosSpawnData = new SOSSpawnData(Data, SpawnTime, false, true, EffectCount);
				SosSpawnData->Depend();
				AddData(ForwardsSpawnTimes, SosSpawnData, i);
				j++;
				SpawnTime += FMath::RandRange(MinSpawnIn, MaxSpawnIn);
			}
		}
		else
		{
			auto Delay = FMath::RandRange(MinSpawnIn, MaxSpawnIn);
			auto SosSpawnData = new SOSSpawnData(Data, Delay, false, true, EffectCount);
			AddData(DelayType == &EnumLikeValue::SOS_DELAY_FROM_END ? BackwardsSpawnTimes : ForwardsSpawnTimes, SosSpawnData, i);
		}
	}
}

void ACallbackSystemDriver::Finalize()
{
	for (int i = 0; i < ParticleCount; ++i)
	{
		ForwardsSpawnTimes[i].Sort();
		BackwardsSpawnTimes[i].Sort([](SOSSpawnData l, SOSSpawnData r) { return l > r; });
	}
	System->SetNiagaraVariableObject("CallbackHandler", this);
	TArray<float> Forwards = TArray<float>();
	this->GetTimingsArray(Forwards, false);
	UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayFloat(System, "ForwardsCallbackPoints", Forwards);
	TArray<float> Backwards = TArray<float>();
	this->GetTimingsArray(Backwards, true);
	UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayFloat(System, "BackwardsCallbackPoints", Backwards);

	UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayInt32(System, "ForwardsAcks", ForwardsAcks);
	UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayInt32(System, "BackwardsAcks", BackwardsAcks);
	System->SetBoolParameter("EnableCallbacks", true);
}

void ACallbackSystemDriver::AddData(TArray<TArray<SOSSpawnData*>>& Array, SOSSpawnData* Data, int ParticleNum)
{
	Data->Depend();
	Array[ParticleNum].Add(Data);
}
