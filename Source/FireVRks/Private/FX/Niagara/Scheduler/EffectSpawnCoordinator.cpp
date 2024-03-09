// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/Niagara/Scheduler/EffectSpawnCoordinator.h"

#include "FX/Niagara/Scheduler/SystemSpawnData.h"
#include "Util/DFStatics.h"
#include "World/Launcher/GenericFireworkLauncher.h"

void UEffectSpawnCoordinator::TickTesting(float DeltaSeconds)
{
	for (int i = TestQueue.Num() - 1; i >= 0; i--)
	{
		auto Val = (TestQueue)[i];
		Val->SetSpawnIn(Val->GetSpawnIn() - DeltaSeconds);
		if (Val->GetSpawnIn() <= 0)
		{
			SpawnEffect(Val);
			TestQueue.RemoveAt(i);
		}
	}
}

void UEffectSpawnCoordinator::TickDisplay(float Position)
{
	if (NumSkip <= 0)
	{
		float StartTime = CurrentPlaybackPosition;
		float EndTime = Position;
		for (int i = 0; i < DisplayQueue.Num(); i++)
		{
			if (DisplayQueue[i]->GetSpawnIn() >= StartTime)
			{
				if (DisplayQueue[i]->GetSpawnIn() < EndTime)
				{
					SpawnEffect(DisplayQueue[i]);
				}
				else
				{
					break;
				}
			}
		}
		CurrentPlaybackPosition = Position;
	}
	NumSkip--;
}

void UEffectSpawnCoordinator::SpawnEffect(ULaunchSettings* Data)
{
	auto Target = Data->GetSpawnTarget();
	if (auto Launcher = Cast<AGenericFireworkLauncher>(Target))
	{
		Launcher->Fire(Data);
		return;
	}
	FVector Location = FVector(0, 0, 0);
	if (Target)
	{
		Location = Target->GetActorLocation();
	}
	Data->GetSystem()->SpawnSystem(USystemSpawnData::New(Data, Data->GetContext(), Location, FVector(1, 0, 0)));
}

void UEffectSpawnCoordinator::EnqueueDisplay(ULaunchSettings* Data)
{
	int i = 0;
	while (i < DisplayQueue.Num() && *DisplayQueue[i] < *Data)
	{
		i++;
	}
	DisplayQueue.Insert(Data, i);
}

void UEffectSpawnCoordinator::Seek(float Location)
{
	CurrentPlaybackPosition = Location;
	NumSkip = 2;
}

void UEffectSpawnCoordinator::Reset()
{
	TestQueue.Empty();
	DisplayQueue.Empty();
}

void UEffectSpawnCoordinator::EnqueueTest(ULaunchSettings* Data)
{
	auto Queue = &TestQueue;

	if (Queue->IsEmpty())
	{
		Queue->Add(Data);
	}
	else
	{
		int i = 0;
		while (i < Queue->Num() && *(*Queue)[i] > *Data)
		{
			i++;
		}
		Queue->Insert(Data, i);
	}
}

UEffectSpawnCoordinator* UEffectSpawnCoordinator::New()
{
	return UDFStatics::New<UEffectSpawnCoordinator>();
}
