#pragma once
#include "LaunchSettings.h"
#include "NiagaraComponent.h"
#include "NiagaraDataInterfaceExport.h"
#include "FX/Niagara/SystemSettings/Enums/EnumLikeValue.h"
#include "FX/Niagara/v2/System/SOSSpawnData.h"
#include "CallbackSystemDriver.generated.h"

UCLASS()
class FIREVRKS_API ACallbackSystemDriver : public AActor, public INiagaraParticleCallbackHandler
{
	GENERATED_BODY()

	UPROPERTY()
	UNiagaraComponent* System;

	TArray<TArray<SOSSpawnData*>> ForwardsSpawnTimes;
	TArray<TArray<SOSSpawnData*>> BackwardsSpawnTimes;
	TArray<int> ForwardsAcks;
    TArray<int> BackwardsAcks;
	int ParticleCount = 0;
	int MaxLifetime = 0;

public:

	virtual void ReceiveParticleData_Implementation(const TArray<FBasicParticleData>& Data, UNiagaraSystem* NiagaraSystem, const FVector& SimulationPositionOffset) override;

	
	virtual void Tick(float DeltaSeconds) override;

	void Init(int ParentParticleCount, float maxLifetime, UNiagaraComponent* BSystem);

	void AddSpawnInfo(ULaunchSettings* Data, float MinSpawnIn, float MaxSpawnIn, int EffectCount, EnumLikeValue* DelayType, int MaxEffects);

	void Finalize();

	void AddData(TArray<TArray<SOSSpawnData*>>& Array, SOSSpawnData* Data, int ParticleNum);

	void GetTimingsArray(TArray<float>& Array, bool Backwards);

};

