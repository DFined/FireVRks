#pragma once
#include "DFAnchor.h"
#include "NiagaraSystem.h"
#include "FX/Niagara/Scheduler/EffectSpawnCoordinator.h"
#include "FX/Niagara/v2/System/EffectSystemManager.h"
#include "World/Launcher/LauncherManager.h"
#include "DFStatics.generated.h"

class UArrayLaunchPattern;

UCLASS()
class FIREVRKS_API UDFStatics : public UObject
{
	GENERATED_BODY()

public:
	static UDFAnchor* const ANCHOR;

	static UDFId* const DEFAULT_SYSTEM_ID;
	static UStaticMesh* const SPHERE_MESH;
	static UNiagaraSystem* const DEFAULT_SYSTEM;
	static UNiagaraSystem* const TRAIL_SYSTEM;
	static ULauncherManager* const LAUNCHER_MANAGER;
	static UArrayLaunchPattern* const ARRAY_LAUNCH_PATTERN;
	static UEffectSystemManager* const EFFECT_SYSTEM_MANAGER;
	static UEffectSpawnCoordinator* const EFFECT_SPAWN_COORDINATOR;
	static AActor* Player;

	UFUNCTION(BlueprintCallable)
	static ULauncherManager* GetLauncherManager();

	UFUNCTION(BlueprintCallable)
	static UArrayLaunchPattern* GetArrayLaunchPattern();

	//Should be called on beginning play to clear globals
	UFUNCTION(BlueprintCallable)
	static void Reset();

	UFUNCTION(BlueprintCallable)
	static TArray<FString> GetFiles(FString FileTypes);

	UFUNCTION(BlueprintCallable)
	static UEffectSpawnCoordinator* GetCoordinator();

	template <class Type>
	static Type* New();

	static AActor* GetPlayer();

	UFUNCTION(BlueprintCallable)
	static void SetPlayer(AActor* bPlayer);

	static UEffectSystem* GetDefaultEffectSystem();
};

template <class Type>
Type* UDFStatics::New()
{
	auto Obj = NewObject<Type>(ANCHOR, Type::StaticClass());
	ANCHOR->Anchor(Obj);
	return Obj;
}
