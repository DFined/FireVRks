#pragma once
#include "NiagaraComponent.h"
#include "FX/Niagara/Scheduler/LaunchSettings.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UFireworkShellBase.generated.h"

UCLASS()
class FIREVRKS_API AFireworkShellBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	UEffectSystem* System;
	UPROPERTY()
	UParameterValueContext* Context;
	UPROPERTY()	
	UProjectileMovementComponent* Component;
	UPROPERTY()
	ULaunchSettings* Settings;
	UPROPERTY()
	UNiagaraComponent* Emitter;
	
	float Lifetime;
	bool IsSpawned = false;

public:
	AFireworkShellBase();
	void Spawn();
	UFUNCTION()
	void DestroyShell(UNiagaraComponent* PSystem);
	virtual void Tick(float DeltaSeconds) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	static AFireworkShellBase* MakeShell(
		UObject* ContextObject, FVector* Location, FRotator* Rotation, ULaunchSettings* Settings
	);

	virtual void BeginDestroy() override;
};
