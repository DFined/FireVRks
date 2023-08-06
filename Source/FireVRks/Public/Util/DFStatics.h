#pragma once
#include "NiagaraSystem.h"
#include "FX/Niagara/Scheduler/EffectSystemScheduler.h"
#include "World/Launcher/LauncherManager.h"
#include "DFStatics.generated.h"

UCLASS()
class UDFStatics : public UObject
{
	GENERATED_BODY()
public:
	static UStaticMesh* const SPHERE_MESH;
	static UNiagaraSystem* const DEFAULT_SYSTEM;
	static UNiagaraSystem* const TRAIL_SYSTEM;
	static UEffectSystemScheduler* const EFFECT_SYSTEM_SCHEDULER;
	static ULauncherManager* const LAUNCHER_MANAGER;

	
	UFUNCTION(BlueprintCallable)
	static UEffectSystemScheduler* GetEffectSystemScheduler();

	UFUNCTION(BlueprintCallable)
	static ULauncherManager* GetLauncherManager();

	//Should be called on beginning play to clear globals
	UFUNCTION(BlueprintCallable)
	static void Reset();
};
