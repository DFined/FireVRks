#pragma once
#include "EffectSystemScheduler.generated.h"


class EffectSpawnData;

/**
 * Basic async effect spawner class. Pretty self explanatory "schedule doing X in Y seconds from now"
 */
UCLASS(BlueprintType)
class UEffectSystemScheduler : public UObject
{
	GENERATED_BODY()

	bool IsTicking;
	
	TArray<EffectSpawnData*> SpawnQueue;

	UPROPERTY()
	AActor* PlayerRef;
	

	UEffectSystemScheduler();

public:
	static UEffectSystemScheduler* MakeInstance();

	UFUNCTION(BlueprintCallable)
	void EnableTicking();

	UFUNCTION(BlueprintCallable)
	void DisableTicking();
	
	void ScheduleSpawn(EffectSpawnData* Data);

	UFUNCTION(BlueprintCallable)
	void Tick(double deltaTime);

	void SpawnNow(EffectSpawnData* Data);

	void SpawnNow(UEffectSystem* System, AActor* SpawnTarget, FVector Offset, FVector UpwardVector, ParameterValueContext* Context);

	UFUNCTION(BlueprintCallable)
	AActor* GetPlayerRef() const;

	UFUNCTION(BlueprintCallable)
	void SetPlayerRef(AActor* InPlayerRef);

private:
	void RemoveSpawn(int i);
};
