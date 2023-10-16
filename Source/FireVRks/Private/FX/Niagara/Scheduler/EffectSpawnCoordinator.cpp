// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/Niagara/Scheduler/EffectSpawnCoordinator.h"

#include "Util/DFStatics.h"

void UEffectSpawnCoordinator::Tick(bool IsTest, float DeltaSeconds)
{
	auto Queue = IsTest ? &TestQueue : &DisplayQueue;
	for (int i = Queue->Num() - 1; i >= 0; i--)
	{
		auto Val = (*Queue)[i];
		Val->SetSpawnIn(Val->GetSpawnIn() - DeltaSeconds);
		if (Val->GetSpawnIn() <= 0)
		{
			SpawnEffect(Val);
			Queue->RemoveAt(i);
		}
	}
}

void UEffectSpawnCoordinator::SpawnEffect(ULaunchSettings* Data)
{
	auto Target = Data->GetSpawnTarget();
	if (auto Launcher = Cast<AGenericFireworkLauncher>(Target))
	{
		Launcher->Fire(Data);
	}
}


void UEffectSpawnCoordinator::Enqueue(bool IsTest, ULaunchSettings* Data)
{
	auto Queue = IsTest ? &TestQueue : &DisplayQueue;

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
