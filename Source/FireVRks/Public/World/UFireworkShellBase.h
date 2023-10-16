#pragma once
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
	
	float Lifetime;

public:
	AFireworkShellBase();
	void Spawn();
	virtual void Tick(float DeltaSeconds) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	static AFireworkShellBase* MakeShell(
		UObject* ContextObject, FVector* Location, FRotator* Rotation, ULaunchSettings* Settings
	);

	virtual void BeginDestroy() override;
};
