#pragma once
#include "GenericLauncherArray.h"
#include "Util/DFU.h"
#include "World/Launcher/GenericFireworkLauncher.h"
#include "LauncherManager.generated.h"

UCLASS(BlueprintType, Blueprintable)
class FIREVRKS_API ULauncherManager : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<AGenericFireworkLauncher*> Launchers = TArray<AGenericFireworkLauncher*>();
	UPROPERTY()
	TMap<FString, UGenericLauncherArray*> Arrays = TMap<FString, UGenericLauncherArray*>();

public:
	UFUNCTION(BlueprintCallable)
	TArray<FString> GetLauncherNames();

	UFUNCTION(BlueprintCallable)
	TArray<UGenericLauncherArray*> GetLaunchers(TArray<UGenericLauncherArray*> Res);

	UFUNCTION(BlueprintCallable)
	UGenericLauncherArray* CreateLauncherArray(FString Name);

	UFUNCTION(BlueprintCallable)
	ULauncherData* AddLauncher(FVector Location, FRotator Rotation, UObject* WorldContextObject, FString ArrayName);
	
	ULauncherData* MakeLauncher(FVector Location, FRotator Rotation, UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable)
	UGenericLauncherArray* FindLauncherArray(FString Name);

	UFUNCTION(BlueprintCallable)
	void Materialize(UObject* WCO);

	TMap<FString, UGenericLauncherArray*>& GetArrays();
	void Reset();

	// static ULauncherManager* MakeInstance()
	// {
	// 	auto Instance = NewObject<ULauncherManager>(GetTransientPackage());
	// 	Instance->AddToRoot();
	// 	return Instance;
	// }

	UFUNCTION(BlueprintCallable)
	static ULauncherManager* GetInstance()
	{
		if (!SingleInstance.IsValid())
		{
			SingleInstance = NewObject<ULauncherManager>();
			SingleInstance->AddToRoot();
		}
		return SingleInstance.Get();
	}

private:
	inline static TWeakObjectPtr<ULauncherManager> SingleInstance = nullptr;
};
