#include "World/Launcher/LauncherManager.h"

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
	for(FString Key: Names)
	{
		Res.Add(*Arrays.Find(Key));
	}
	return Res;
}

void ULauncherManager::AddLauncher(AGenericFireworkLauncher* Launcher)
{
	Launchers.Add(Launcher);	
}

UGenericLauncherArray* ULauncherManager::CreateLauncherArray(FString Name)
{
	if(!Arrays.Contains(Name))
	{
		auto Array = NewObject<UGenericLauncherArray>();
		Array->SetArrayName(Name);
		Arrays.Add(Name, Array);
		return Array;
	}
	return nullptr;
}

void ULauncherManager::AddLauncherToArray(AGenericFireworkLauncher* Launcher, FString ArrayName)
{
	auto Arr = Arrays.Find(ArrayName);
	if(Arr)
	{
		(*Arr)->AddLauncher(Launcher);
		Launchers.Add(Launcher);
	}
}
