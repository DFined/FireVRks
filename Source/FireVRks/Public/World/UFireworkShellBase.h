#pragma once
#include "FX/Niagara/Scheduler/EffectSpawnData.h"
#include "UFireworkShellBase.generated.h"

UCLASS()
class FIREVRKS_API AFireworkShellBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	UEffectSpawnData* SpawnData;

	float Lifetime;

public:
	AFireworkShellBase();
	void Spawn();
	virtual void Tick(float DeltaSeconds) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	static AFireworkShellBase* MakeShell(
		UObject* ContextObject, FVector* Location, FRotator* Rotation, UEffectSystem* System, UParameterValueContext* Context, float Lifetime, float Velocity
	);

	virtual void BeginDestroy() override;
};
