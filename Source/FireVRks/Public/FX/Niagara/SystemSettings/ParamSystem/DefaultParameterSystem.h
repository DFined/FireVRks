#pragma once
#include "CompoundableFormalParameter.h"
#include "NiagaraSystem.h"
#include "FX/Niagara/SystemSettings/FormalParameter/BlockCompoundParameter.h"
#include "FX/Niagara/SystemSettings/FormalParameter/EnumFormalParameter.h"
#include "DefaultParameterSystem.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UDefaultParameterSystem : public UObject
{
	GENERATED_BODY()
	static TArray<AbstractFormalParameter*> Parameters;
	static bool IsInit;
public:
	static BlockCompoundParameter MAIN_SETTINGS_BLOCK;
	static EnumFormalParameter EFFECT_SHAPE;
	static BlockCompoundParameter PEONY_SETTINGS_BLOCK;

	static CompoundableFormalParameter<int> VELOCITY;
	static CompoundableFormalParameter<float> LIFETIME;
	static CompoundableFormalParameter<int> SPRITE_SIZE;
	
	static FormalParameter<FLinearColor> MAIN_COLOR;
	static FormalParameter<int> SPRITE_COUNT;

	static FormalParameter<bool> USE_DISTANCE_CORRECTION;
	static FormalParameter<float> DISTANCE_CORRECTION_SCALE;

	static UNiagaraSystem* DEFAULT_SYSTEM;

	/**
	 * TRAIL SETTINGS
	 */
	static BlockCompoundParameter TRAIL_SETTINGS_BLOCK;
	
	static BlockCompoundParameter SMOKE_TRAIL_SETTINGS_BLOCK;
	static FormalParameter<bool> USE_SMOKE_TRAIL;
	
	
	static BlockCompoundParameter CRACKLE_TRAIL_SETTINGS_BLOCK;
	static FormalParameter<bool> USE_CRACKLE_TRAIL;
	
	static BlockCompoundParameter WILLOW_TRAIL_SETTINGS_BLOCK;
	static FormalParameter<bool> USE_WILLOW_TRAIL;

	static BlockCompoundParameter COLOR_EFFECT_SETTINGS;
	static BlockCompoundParameter LERP_COLOR_BLOCK;
	static FormalParameter<bool> USE_COLOR_LERP;
	static FormalParameter<FLinearColor> SECONDARY_COLOR;

	static void Initialize();

	static void AddParameter(AbstractFormalParameter* Parameter);

	static TArray<AbstractFormalParameter*> GetParameters()
	{
		return Parameters;
	}
	
	ParameterValueContext* Context;

	void SetContext(ParameterValueContext* bContext)
	{
		this->Context = bContext;
	}

	UFUNCTION(BlueprintCallable)
	void SpawnSystem(AActor* Target);
};
