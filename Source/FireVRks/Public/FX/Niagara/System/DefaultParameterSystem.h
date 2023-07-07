#pragma once
#include "EffectSystem.h"
#include "NiagaraSystem.h"
#include "FX/Niagara/SystemSettings/FormalParameter/BlockCompoundParameter.h"
#include "FX/Niagara/SystemSettings/FormalParameter/EnumFormalParameter.h"
#include "FX/Niagara/SystemSettings/FormalParameter/ListFormalParameter.h"
#include "FX/Niagara/SystemSettings/FormalParameter/SystemInstantiationFormalParameter.h"
#include "FX/Niagara/SystemSettings/ParamSystem/CompoundableFormalParameter.h"
#include "DefaultParameterSystem.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UDefaultParameterSystem : public UEffectSystem
{
	
	GENERATED_BODY()
	TArray<AbstractFormalParameter*> Parameters = TArray<AbstractFormalParameter*>();
	bool IsInit = false;


public:
	UDefaultParameterSystem() = default;

	BlockCompoundParameter MAIN_SETTINGS_BLOCK = BlockCompoundParameter("Effect Settings", true, true, true);

	CompoundableFormalParameter<int> VELOCITY = CompoundableFormalParameter("Velocity", DFType::TYPED_INT_PARAMETER, true, 15000);
	CompoundableFormalParameter<float> LIFETIME = CompoundableFormalParameter("Sprite Lifetime", DFType::TYPED_FLOAT_PARAMETER, true, 5.0f);
	CompoundableFormalParameter<int> SPRITE_SIZE = CompoundableFormalParameter("Sprite size", DFType::TYPED_INT_PARAMETER, true, 100);


	FormalParameter<bool> USE_SECOND_COLOR = FormalParameter(DFType::TYPED_BOOL_PARAMETER, "Dual color", true, false, true);
	FormalParameter<FLinearColor> MAIN_COLOR = FormalParameter(DFType::TYPED_VECTOR_PARAMETER, "Main color", true, FLinearColor(255, 0, 0), true);
	FormalParameter<FLinearColor> SECONDARY_COLOR = FormalParameter(DFType::TYPED_VECTOR_PARAMETER, "Secondary color", true, FLinearColor(1, 1, 255), true);
	FormalParameter<int> SPRITE_COUNT = FormalParameter(DFType::TYPED_INT_PARAMETER, "Star count", true, 100, true);
	EnumFormalParameter EFFECT_ROTATION_TYPE = EnumFormalParameter("Effect orientation", true, &EnumLike::EFFECT_ROTATION_SETTING, true);	
	FormalParameter<FLinearColor> NORMAL_VECTOR = FormalParameter(DFType::TYPED_VECTOR_PARAMETER, "Direction", true, FLinearColor(0, 0.5, 1), true);
	

	UPROPERTY()
	UNiagaraSystem* DEFAULT_SYSTEM = nullptr;

	/**SHAPE SETTINGS*/
	EnumFormalParameter EFFECT_SHAPE = EnumFormalParameter("Effect shape", true, &EnumLike::BURST_SHAPE, true);
	BlockCompoundParameter CONE_SETTINGS_BLOCK = BlockCompoundParameter("Cone settings", true, true, true);
	FormalParameter<int> CONE_ANGLE = FormalParameter(DFType::TYPED_INT_PARAMETER, "Cone angle", true, 30, true);
	FormalParameter<int> CONE_ANGLE_VARIANCE = FormalParameter(DFType::TYPED_INT_PARAMETER, "Cone angle variance", true, 30, true);
	FormalParameter<bool> CONE_SURFACE_ONLY = FormalParameter(DFType::TYPED_BOOL_PARAMETER, "Thin cone", true, false, true);
	FormalParameter<bool> CONE_UNIFORM = FormalParameter(DFType::TYPED_BOOL_PARAMETER, "Uniform", true, false, true);
	FormalParameter<bool> CONE_BI_DIRECTIONAL = FormalParameter(DFType::TYPED_BOOL_PARAMETER, "Bi directional", true, false, true);
	FormalParameter<int> CLUSTER_SIZE = FormalParameter(DFType::TYPED_INT_PARAMETER, "Cluster size", true, 1, true);
	FormalParameter<float> CLUSTER_SPACING = FormalParameter(DFType::TYPED_FLOAT_PARAMETER, "Cluster spacing", true, 0.5f, true);


	/**
	 * COLOR SETTINGS
	 */
	BlockCompoundParameter COLOR_EFFECT_SETTINGS = BlockCompoundParameter("Color effects", true, true, false);;
	EnumFormalParameter COLOR_EFFECT_TYPE = EnumFormalParameter("Color effect type", true, &EnumLike::COLOR_EFFECT, true);
	FormalParameter<FLinearColor> TARGET_COLOR = FormalParameter(DFType::TYPED_VECTOR_PARAMETER, "Target color", true, FLinearColor(255, 255, 255), true);
	FormalParameter<float> LERP_START_TIME = FormalParameter(DFType::TYPED_FLOAT_PARAMETER, "Change start time", true, 1.0f, true);
	FormalParameter<float> LERP_END_TIME = FormalParameter(DFType::TYPED_FLOAT_PARAMETER, "Change end time", true, 2.0f, true);

	BlockCompoundParameter SIMPLE_COLOR_CHANGE_BLOCK = BlockCompoundParameter("Simple color change", true, true, false);

	BlockCompoundParameter COLOR_FLARE_BLOCK = BlockCompoundParameter("Color flare", true, true, false);
	FormalParameter<int> COLOR_FLARE_GROUP_COUNT = FormalParameter(DFType::TYPED_INT_PARAMETER, "Group count", true, 1, true);

	BlockCompoundParameter COLOR_FLICKER_BLOCK = BlockCompoundParameter("Color flicker", true, true, false);

	BlockCompoundParameter COLOR_WAVE_BLOCK = BlockCompoundParameter("Color wave", true, true, false);
	FormalParameter<int> WAVE_CYCLE_PERCENT = FormalParameter(DFType::TYPED_INT_PARAMETER, "Wave cycle percent", true, 80, true);

	BlockCompoundParameter ADVANCE_COLOR_LERP_BLOCK = BlockCompoundParameter("Advanced lerp", true, true, false);
	FormalParameter<float> LERP_FREQUENCY = FormalParameter(DFType::TYPED_FLOAT_PARAMETER, "Lerp frequency", true, 1.0f, true);
	FormalParameter<int> LERP_PHASE_COUNT = FormalParameter(DFType::TYPED_INT_PARAMETER, "Wave phase count", true, 100, true);
	FormalParameter<float> LERP_WAVE_DUTY_CYCLE = FormalParameter(DFType::TYPED_FLOAT_PARAMETER, "Lerp wave duty cycle", true, 0.0f, true);

	/**
	 * CompoundSystem
	 */
	
	BlockCompoundParameter SOS_CONFIG_BLOCK = BlockCompoundParameter("Sos configuration", true, true, true);
	ListFormalParameter SOS_CONFIGS_LIST = ListFormalParameter("Shell-of-shells", &SOS_CONFIG_BLOCK, true, true);
	FormalParameter<int> SOS_CHILD_SHELLS_NUM = FormalParameter(DFType::TYPED_INT_PARAMETER, "Num child shells", true, 15, true);
	EnumFormalParameter SOS_EFFECT_SHAPE = EnumFormalParameter("Child effects shape", true, &EnumLike::SOS_SHAPE, true);
	CompoundableFormalParameter<float> SOS_EFFECT_TIME = CompoundableFormalParameter("Sos effect time", DFType::TYPED_FLOAT_PARAMETER, true, 2.0f);
	SystemInstantiationFormalParameter SOS_EFFECT_PICKER = SystemInstantiationFormalParameter("Child effect",true);
	CompoundableFormalParameter<int> SOS_SHAPE_SCALE = CompoundableFormalParameter<int>("Shape scale", DFType::TYPED_INT_PARAMETER, true, 8000);
	FormalParameter<FLinearColor> SOS_SHAPE_NORMAL = FormalParameter(DFType::TYPED_VECTOR_PARAMETER, "SOS Shape normal", true, FLinearColor(0,1.0,1.0), true);
	BlockCompoundParameter SOS_RING_BLOCK = BlockCompoundParameter("Ring settings", true, true, true);
	BlockCompoundParameter SOS_SPHERE_BLOCK = BlockCompoundParameter("Sphere settings", true, true, true);
	EnumFormalParameter SOS_DELAY_TYPE = EnumFormalParameter("Delay type", true, &EnumLike::SOS_DELAY_TYPE, true);
	FormalParameter<int> SOS_RECURRING_MAX_NUM = FormalParameter(DFType::TYPED_INT_PARAMETER, "Maximum effects", true, 4, true);


	FormalParameter<bool> USE_DISTANCE_CORRECTION = FormalParameter(DFType::TYPED_BOOL_PARAMETER, "Use distance correction", false, true, true);
	BlockCompoundParameter DISTANCE_CORRECTION_SETTINGS = BlockCompoundParameter("Distance correction settings", true, true, true);
	FormalParameter<float> DISTANCE_CORRECTION_SCALE = FormalParameter(DFType::TYPED_FLOAT_PARAMETER, "Correction linear scale", true, 1.0f, true);
	FormalParameter<float> DISTANCE_CORRECTION_EXPONENT = FormalParameter(DFType::TYPED_FLOAT_PARAMETER, "Correction exponent", true, 0.5f, true);
	
	BlockCompoundParameter DRAG_SETTINGS = BlockCompoundParameter("Aerodynamic drag", false, true, false);
	FormalParameter<float> DRAG_EXPONENT = FormalParameter(DFType::TYPED_FLOAT_PARAMETER, "Drag exponent", true, 0.2f, true);
	FormalParameter<float> DRAG_LOW_SPEED_SCALE = FormalParameter(DFType::TYPED_FLOAT_PARAMETER, "Drag low speed scale", true, 1.f, true);
	FormalParameter<float> DRAG_HIGH_SPEED_SCALE = FormalParameter(DFType::TYPED_FLOAT_PARAMETER, "Drag high speed scale", true, 1.f, true);

	/**
	 * TRAIL SETTINGS
	 */
	BlockCompoundParameter TRAIL_SETTINGS_BLOCK = BlockCompoundParameter("Trails", true, true, true);

	BlockCompoundParameter SMOKE_TRAIL_SETTINGS_BLOCK = BlockCompoundParameter("Smoke trail settings", true, true, false);
	FormalParameter<bool> USE_SMOKE_TRAIL = FormalParameter(DFType::TYPED_BOOL_PARAMETER, "Use smoke trail", true, false, true);
	FormalParameter<float> SMOKE_TRAIL_SPREAD = FormalParameter(DFType::TYPED_FLOAT_PARAMETER, "Smoke Trail Spread", true, 0.0f, true);
	FormalParameter<float> SMOKE_TRAIL_LIFETIME = FormalParameter(DFType::TYPED_FLOAT_PARAMETER, "Smoke Trail Lifetime", true, 3.0f, true);
	FormalParameter<float> SMOKE_TRAIL_INTENSITY = FormalParameter(DFType::TYPED_FLOAT_PARAMETER, "Smoke Trail Intensity", false, 1.0f, true);
	FormalParameter<int> SMOKE_TRAIL_SPRITE_SIZE = FormalParameter(DFType::TYPED_INT_PARAMETER, "Smoke Trail Sprite Size", true, 500, true);
	FormalParameter<float> SMOKE_TRAIL_EMISSION_DURATION = FormalParameter(DFType::TYPED_FLOAT_PARAMETER, "Smoke Trail Emission Duration", false, 4.0f, true);

	BlockCompoundParameter CRACKLE_TRAIL_SETTINGS_BLOCK = BlockCompoundParameter("Crackle trail settings", true, true, false);
	FormalParameter<bool> USE_CRACKLE_TRAIL = FormalParameter(DFType::TYPED_BOOL_PARAMETER, "Use crackle trail", true, false, true);
	FormalParameter<float> CRACKLE_TRAIL_SPREAD = FormalParameter(DFType::TYPED_FLOAT_PARAMETER, "Crackle Trail Spread", false, 1.5f, true);
	FormalParameter<float> CRACKLE_TRAIL_EJECTION_SPEED = FormalParameter(DFType::TYPED_FLOAT_PARAMETER, "Crackle Trail Ejection Speed", true, 0.0f, true);
	CompoundableFormalParameter<float> CRACKLE_TRAIL_LIFETIME = CompoundableFormalParameter("Crackle trail lifetime", DFType::TYPED_FLOAT_PARAMETER, true, 0.6f);
	FormalParameter<float> CRACKLE_TRAIL_SPRITE_SIZE = FormalParameter(DFType::TYPED_FLOAT_PARAMETER, "Crackle Trail Sprite Size", false, 4.0f, true);
	FormalParameter<int> CRACKLE_TRAIL_SPAWN_RATE = FormalParameter(DFType::TYPED_INT_PARAMETER, "Crackle Trail Spawn Rate", true, 200, true);
	FormalParameter<float> CRACKLE_TRAIL_EMISSION_DURATION = FormalParameter(DFType::TYPED_FLOAT_PARAMETER, "Crackle Trail Emission Duration", true, 3.0f, true);

	
	BlockCompoundParameter WILLOW_TRAIL_SETTINGS_BLOCK = BlockCompoundParameter("Willow trail settings", true, true, false);
	FormalParameter<bool> USE_WILLOW_TRAIL = FormalParameter(DFType::TYPED_BOOL_PARAMETER, "Use willow trail", true, false, true);
	FormalParameter<float> WILLOW_TRAIL_SPREAD = FormalParameter(DFType::TYPED_FLOAT_PARAMETER, "Willow Trail Spread", false, 0.10f, true);
	FormalParameter<float> WILLOW_TRAIL_EJECTION_SPEED = FormalParameter(DFType::TYPED_FLOAT_PARAMETER, "Willow Trail Ejection Speed", true, 0.0f, true);
	CompoundableFormalParameter<float> WILLOW_TRAIL_LIFETIME = CompoundableFormalParameter("Willow trail lifetime", DFType::TYPED_FLOAT_PARAMETER, true, 3.0f, 4.0f);
	FormalParameter<float> WILLOW_TRAIL_SPRITE_SIZE = FormalParameter(DFType::TYPED_FLOAT_PARAMETER, "Willow Trail Sprite Size", false, 35.0f, true);
	FormalParameter<int> WILLOW_TRAIL_SPAWN_RATE = FormalParameter(DFType::TYPED_INT_PARAMETER, "Willow Trail Spawn Rate", true, 150, true);
	FormalParameter<float> WILLOW_TRAIL_EMISSION_DURATION = FormalParameter(DFType::TYPED_FLOAT_PARAMETER, "Willow Trail Emission Duration", true, 5.0f, true);
	

	
	virtual void Initialize() override;

	virtual void SpawnSystem(EffectSpawnData* Data, AActor* PlayerRef) override;

	void AddParameter(AbstractFormalParameter* Parameter);

	TArray<AbstractFormalParameter*> GetParameters() const
	{
		return Parameters;
	}

	static UDefaultParameterSystem* Make()
	{
		auto Sys = NewObject<UDefaultParameterSystem>(GetTransientPackage());
		Sys->AddToRoot();
		return Sys;
	}

	virtual FString GetId() override;

	virtual FString GetName() override;

	virtual UTexture2D* GetIcon() override;

	virtual TArray<AbstractFormalParameter*> GetOuterParameters() override;
};
