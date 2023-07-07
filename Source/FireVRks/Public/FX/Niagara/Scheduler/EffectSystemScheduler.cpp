#include "FX/Niagara/Scheduler/EffectSystemScheduler.h"

#include "FX/Niagara/System/EffectSystem.h"

UEffectSystemScheduler* const UEffectSystemScheduler::INSTANCE = MakeInstance();

UEffectSystemScheduler* UEffectSystemScheduler::MakeInstance()
{
	auto Instance = NewObject<UEffectSystemScheduler>(GetTransientPackage());
	Instance->AddToRoot();
	return Instance;
}

UEffectSystemScheduler::UEffectSystemScheduler()
{
}

void UEffectSystemScheduler::EnableTicking()
{
	IsTicking = true;
}

void UEffectSystemScheduler::DisableTicking()
{
	IsTicking = false;
}

void UEffectSystemScheduler::ScheduleSpawn(EffectSpawnData* Data)
{
	Data->Depend();
	SpawnQueue.Add(Data);
}

void UEffectSystemScheduler::Tick(double deltaTime)
{
	if (IsTicking)
	{
		for (int i = SpawnQueue.Num() - 1; i >= 0; i--)
		{
			EffectSpawnData* Data = SpawnQueue[i];
			auto SpawnIn = Data->GetSpawnIn() - deltaTime;
			if (SpawnIn > 0)
			{
				Data->SetSpawnIn(SpawnIn);
			}
			else
			{
				SpawnNow(Data);
				RemoveSpawn(i);
			}
		}
	}
}

void UEffectSystemScheduler::SpawnNow(EffectSpawnData* Data)
{
	if(Data->IsValid())
	{
		Data->GetSystem()->SpawnSystem(Data, PlayerRef);
	}
}

void UEffectSystemScheduler::SpawnNow(UEffectSystem* System, AActor* SpawnTarget, FVector Offset, FVector UpwardDirection, ParameterValueContext* Context)
{
	auto Data = new EffectSpawnData(System, Context, SpawnTarget,  0, Offset, UpwardDirection);
	if (System && SpawnTarget && Context)
	{
		System->SpawnSystem(Data, PlayerRef);
	}
	delete(Data);
}

UEffectSystemScheduler* UEffectSystemScheduler::GetInstance()
{
	return INSTANCE;
}

AActor* UEffectSystemScheduler::GetPlayerRef() const
{
	return PlayerRef;
}

void UEffectSystemScheduler::SetPlayerRef(AActor* InPlayerRef)
{
	this->PlayerRef = InPlayerRef;
}

void UEffectSystemScheduler::RemoveSpawn(int i)
{
	DFManaged::SafeRelease(SpawnQueue[i]);
	SpawnQueue.RemoveAt(i);
}
