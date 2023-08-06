#pragma once
#include "GenericLauncherArray.h"
#include "World/Launcher/GenericFireworkLauncher.h"
#include "LauncherManager.generated.h"

UCLASS(BlueprintType, Blueprintable)
class ULauncherManager : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<AGenericFireworkLauncher*> Launchers = TArray<AGenericFireworkLauncher*>();
	UPROPERTY()
	TMap<FString,UGenericLauncherArray*> Arrays = TMap<FString,UGenericLauncherArray*>();
	
public:
	UFUNCTION(BlueprintCallable)
	TArray<FString> GetLauncherNames();

	UFUNCTION(BlueprintCallable)
	TArray<UGenericLauncherArray*> GetLaunchers(TArray<UGenericLauncherArray*> Res);

	UFUNCTION(BlueprintCallable)
	UGenericLauncherArray* CreateLauncherArray(FString Name);

	UFUNCTION(BlueprintCallable)
	void AddLauncherToArray(AGenericFireworkLauncher* Launcher, FString ArrayName);

	UFUNCTION(BlueprintCallable)
	void AddLauncher(AGenericFireworkLauncher* Launcher);

	// This is necessary due to statics not being reset on PIE restart, only on editor restart
	UFUNCTION(BlueprintCallable)
	void Reset()
	{
		Arrays.Empty();
		Launchers.Empty();
	}

	static ULauncherManager* MakeInstance()
	{
		auto Instance = NewObject<ULauncherManager>(GetTransientPackage());
		Instance->AddToRoot();
		return Instance;
	}
};

