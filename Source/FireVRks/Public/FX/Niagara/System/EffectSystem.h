#pragma once
#include "ParameterProvider.h"
#include "FX/Niagara/Scheduler/EffectSpawnData.h"
#include "FX/Niagara/SystemSettings/InstanceParameter/ParameterValueContextProvider.h"
#include "Unsafe/DFStyleUtil.h"
#include "EffectSystem.generated.h"

UCLASS(Abstract)
class UEffectSystem : public UObject, public ParameterProvider
{
	GENERATED_BODY()

public:
	UEffectSystem() = default;

	virtual void Initialize();

	virtual void SpawnSystem(EffectSpawnData* Data, AActor*);

	virtual FString GetId() PURE_VIRTUAL("GetId", return "";);
	
	virtual UTexture2D* GetIcon() PURE_VIRTUAL("GetIcon", return DFStyleUtil::DEFAULT_TEXTURE;);

	virtual FString GetName() PURE_VIRTUAL("GetName", return "";);

	virtual TArray<AbstractFormalParameter*> GetOuterParameters() override;

	virtual UParameterValueContextProvider* GetContextProvider() PURE_VIRTUAL("GetContextProvider", return nullptr;);
};
