#pragma once
#include "FX/Niagara/Scheduler/EffectSpawnData.h"
#include "FX/Niagara/SystemSettings/InstanceParameter/ParameterValueContext.h"
#include "FX/Niagara/SystemSettings/InstanceParameter/ParameterValueContextProvider.h"
#include "Unsafe/DFStyleUtil.h"
#include "EffectSystem.generated.h"

UCLASS(Abstract)
class UEffectSystem : public UObject
{
	GENERATED_BODY()

public:
	UEffectSystem() = default;

	virtual void Initialize();

	virtual void SpawnSystem(EffectSpawnData* Data, AActor*);

	virtual FString GetId() PURE_VIRTUAL("GetId", return "";);
	
	virtual UTexture2D* GetIcon() PURE_VIRTUAL("GetIcon", return DFStyleUtil::DEFAULT_TEXTURE;);

	virtual FString GetName() PURE_VIRTUAL("GetName", return "";);

	virtual TArray<AbstractFormalParameter*> GetOuterParameters() {return TArray<AbstractFormalParameter*>();}

	virtual UParameterValueContextProvider* GetContextProvider() PURE_VIRTUAL("GetContextProvider", return nullptr;);
};
