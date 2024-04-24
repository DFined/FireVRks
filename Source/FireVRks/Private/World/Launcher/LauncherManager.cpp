#include "World/Launcher/LauncherManager.h"

#include "World/Launcher/LauncherData.h"

TArray<FString> ULauncherManager::GetLauncherNames()
{
	TArray<FString> Names = TArray<FString>();
	Arrays.GetKeys(Names);
	return Names;
}

TArray<UGenericLauncherArray*> ULauncherManager::GetLaunchers(TArray<UGenericLauncherArray*> Res)
{
	TArray<FString> Names = TArray<FString>();
	Arrays.GetKeys(Names);
	for (FString Key : Names)
	{
		Res.Add(*Arrays.Find(Key));
	}
	return Res;
}

UGenericLauncherArray* ULauncherManager::FindLauncherArray(FString Name)
{
	const auto Array = Arrays.Find(Name);
	return Array ? *Array : nullptr;
}

void ULauncherManager::Materialize(UObject* WCO)
{
	for (auto Array : Arrays)
	{
		for (auto Launcher : Array.Value->GetLaunchers())
		{
			auto World = GEngine->GetWorldFromContextObject(WCO, EGetWorldErrorMode::LogAndReturnNull);
			Launcher->Materialize(World);
		}
	}
}

TMap<FString, UGenericLauncherArray*>& ULauncherManager::GetArrays()
{
	return Arrays;
}

void ULauncherManager::Reset()
{
	Arrays.Empty();
	for(auto Launcher : Launchers)
	{
		Launcher->Destroy();
	}
	Launchers.Empty();
}

UGenericLauncherArray* ULauncherManager::CreateLauncherArray(FString Name)
{
	if (!Arrays.Contains(Name))
	{
		auto Array = NewObject<UGenericLauncherArray>(this, UGenericLauncherArray::StaticClass());
		Array->SetArrayName(Name);
		Arrays.Add(Name, Array);
		return Array;
	}
	return nullptr;
}


ULauncherData* ULauncherManager::AddLauncher(FVector Location, FRotator Rotation, UObject* WorldContextObject, FString ArrayName)
{
	auto LauncherData = MakeLauncher(Location, Rotation, WorldContextObject);
	auto Array = *Arrays.Find(ArrayName);
	Array->AddLauncher(LauncherData);
	return LauncherData;
}

ULauncherData* ULauncherManager::MakeLauncher(FVector Location, FRotator Rotation, UObject* WorldContextObject)
{
	auto LauncherData = ULauncherData::Instance(this, Location, Rotation);
	auto World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	LauncherData->Materialize(World);
	return LauncherData;
}
