#pragma once
#include "EffectSystem.h"
#include "FX/Niagara/Scheduler/EffectSpawnData.h"
#include "FX/Niagara/SystemSettings/Enums/EnumLike.h"
#include "FX/Niagara/v2/ParamUtil.h"
#include "FX/Niagara/v2/FormalParameter/BoolFormalParameter.h"
#include "FX/Niagara/v2/FormalParameter/ColorFormalParameter.h"
#include "FX/Niagara/v2/FormalParameter/CompoundableFormalParameter.h"
#include "FX/Niagara/v2/FormalParameter/FloatFormalParameter.h"
#include "FX/Niagara/v2/FormalParameter/IntFormalParameter.h"
#include "FX/Niagara/v2/FormalParameter/ListFormalParameter.h"
#include "FX/Niagara/v2/FormalParameter/SystemInstantiationFormalParameter.h"
#include "Util/DFStatics.h"
#include "DefaultParameterSystem.generated.h"

UCLASS(Blueprintable, BlueprintType)
class FIREVRKS_API UDefaultParameterSystem : public UEffectSystem
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<UAbstractFormalParameter*> Parameters = TArray<UAbstractFormalParameter*>();

	bool IsInit = false;

public:
	UDefaultParameterSystem() = default;

	UPROPERTY()
	UBlockFormalParameter* MAIN_SETTINGS_BLOCK = UParamUtil::Global<UBlockFormalParameter, bool>("Effect Settings", true, true);

	UPROPERTY()
	UCompoundableFormalParameter* VELOCITY = UCompoundableFormalParameter::New<UIntFormalParameter, int>(UDFStatics::ANCHOR, "Velocity", true, 15000);
	UPROPERTY()
	UCompoundableFormalParameter* LIFETIME = UCompoundableFormalParameter::New<UFloatFormalParameter, float>(UDFStatics::ANCHOR, "Sprite Lifetime", true, 5.0f);
	UPROPERTY()
	UCompoundableFormalParameter* SPRITE_SIZE = UCompoundableFormalParameter::New<UIntFormalParameter, int>(UDFStatics::ANCHOR, "Sprite size", true, 100);

	UPROPERTY()
	UBoolFormalParameter* USE_SECOND_COLOR = UParamUtil::Global<UBoolFormalParameter, bool>("Dual color", true, false);
	UPROPERTY()
	UColorFormalParameter* MAIN_COLOR = UParamUtil::Global<UColorFormalParameter, FLinearColor>("Main color", true, FLinearColor(255, 1, 1));
	UPROPERTY()
	UColorFormalParameter* SECONDARY_COLOR = UParamUtil::Global<UColorFormalParameter, FLinearColor>("Main color", true, FLinearColor(1, 1, 255));
	UPROPERTY()
	UIntFormalParameter* SPRITE_COUNT = UParamUtil::Global<UIntFormalParameter, int>("Star count", true, 100);
	UPROPERTY()
	UEnumFormalParameter* EFFECT_ROTATION_TYPE = UParamUtil::Global<UEnumFormalParameter, EnumLikeValue*>("Effect orientation", true, &EnumLikeValue::RANDOM);
	UPROPERTY()
	UColorFormalParameter* NORMAL_VECTOR = UParamUtil::Global<UColorFormalParameter, FLinearColor>("Direction", true, FLinearColor(0, 0.5, 1));

	/**SHAPE SETTINGS*/
	UPROPERTY()
	UEnumFormalParameter* EFFECT_SHAPE = UParamUtil::Global<UEnumFormalParameter, EnumLikeValue*>("Effect shape", true, &EnumLikeValue::PEONY);
	UPROPERTY()
	UBlockFormalParameter* CONE_SETTINGS_BLOCK = UParamUtil::Global<UBlockFormalParameter, bool>("Cone settings", true, true);
	UPROPERTY()
	UIntFormalParameter* CONE_ANGLE = UParamUtil::Global<UIntFormalParameter, int>("Cone angle", true, 30);
	UPROPERTY()
	UIntFormalParameter* CONE_ANGLE_VARIANCE = UParamUtil::Global<UIntFormalParameter, int>("Cone angle variance", true, 30);
	UPROPERTY()
	UBoolFormalParameter* CONE_SURFACE_ONLY = UParamUtil::Global<UBoolFormalParameter, bool>("Thin cone", true, false);
	UPROPERTY()
	UBoolFormalParameter* CONE_UNIFORM = UParamUtil::Global<UBoolFormalParameter, bool>("Uniform", true, false);
	UPROPERTY()
	UBoolFormalParameter* CONE_BI_DIRECTIONAL = UParamUtil::Global<UBoolFormalParameter, bool>("Bi directional", true, false);
	UPROPERTY()
	UIntFormalParameter* CLUSTER_SIZE = UParamUtil::Global<UIntFormalParameter, int>("Cluster size", true, 1);
	UPROPERTY()
	UFloatFormalParameter* CLUSTER_SPACING = UParamUtil::Global<UFloatFormalParameter, float>("Cluster spacing", true, 0.5f);


	/**
	 * COLOR SETTINGS
	 */
	UPROPERTY()
	UBlockFormalParameter* COLOR_EFFECT_SETTINGS = UParamUtil::Global<UBlockFormalParameter, bool>("Color effects", true, true);
	UPROPERTY()
	UEnumFormalParameter* COLOR_EFFECT_TYPE = UParamUtil::Global<UEnumFormalParameter, EnumLikeValue*>("Color effect type", true, &EnumLikeValue::NO_EFFECT);
	UPROPERTY()
	UColorFormalParameter* TARGET_COLOR = UParamUtil::Global<UColorFormalParameter, FLinearColor>("Target color", true, FLinearColor(255, 255, 255));
	UPROPERTY()
	UFloatFormalParameter* LERP_START_TIME = UParamUtil::Global<UFloatFormalParameter, float>("Change start time", true, 1.0f);
	UPROPERTY()
	UFloatFormalParameter* LERP_END_TIME = UParamUtil::Global<UFloatFormalParameter, float>("Change end time", true, 2.0f);
	UPROPERTY()
	UBlockFormalParameter* SIMPLE_COLOR_CHANGE_BLOCK = UParamUtil::Global<UBlockFormalParameter, bool>("Simple color change", true, true);
	UPROPERTY()
	UBlockFormalParameter* COLOR_FLARE_BLOCK = UParamUtil::Global<UBlockFormalParameter, bool>("Color flare", true, true);
	UPROPERTY()
	UIntFormalParameter* COLOR_FLARE_GROUP_COUNT = UParamUtil::Global<UIntFormalParameter, int>("Group count", true, 1);
	UPROPERTY()
	UBlockFormalParameter* COLOR_FLICKER_BLOCK = UParamUtil::Global<UBlockFormalParameter, bool>("Color flicker", true, true);
	UPROPERTY()
	UBlockFormalParameter* COLOR_WAVE_BLOCK = UParamUtil::Global<UBlockFormalParameter, bool>("Color wave", true, true);
	UPROPERTY()
	UIntFormalParameter* WAVE_CYCLE_PERCENT = UParamUtil::Global<UIntFormalParameter, int>("Wave cycle percent", true, 80);
	UPROPERTY()
	UBlockFormalParameter* ADVANCE_COLOR_LERP_BLOCK = UParamUtil::Global<UBlockFormalParameter, bool>("Advanced lerp", true, true);
	UPROPERTY()
	UFloatFormalParameter* LERP_FREQUENCY = UParamUtil::Global<UFloatFormalParameter, float>("Lerp frequency", true, 1.0f);
	UPROPERTY()
	UIntFormalParameter* LERP_PHASE_COUNT = UParamUtil::Global<UIntFormalParameter, int>("Wave phase count", true, 100);
	UPROPERTY()
	UFloatFormalParameter* LERP_WAVE_DUTY_CYCLE = UParamUtil::Global<UFloatFormalParameter, float>("Lerp wave duty cycle", true, 0.0f);

	/**
	 * CompoundSystem
	 */

	UPROPERTY()
	UBlockFormalParameter* SOS_CONFIG_BLOCK = UParamUtil::Global<UBlockFormalParameter, bool>("Sos configuration", true, true);
	UPROPERTY()
	UListFormalParameter* SOS_CONFIGS_LIST = UParamUtil::Global<UListFormalParameter, UAbstractFormalParameter*>("Shell-of-shells", true, SOS_CONFIG_BLOCK);
	UPROPERTY()
	UIntFormalParameter* SOS_CHILD_SHELLS_NUM = UParamUtil::Global<UIntFormalParameter, int>("Num child shells", true, 15);
	UPROPERTY()
	UEnumFormalParameter* SOS_EFFECT_SHAPE = UParamUtil::Global<UEnumFormalParameter, EnumLikeValue*>("Child effects shape", true, &EnumLikeValue::SOS_SPHERE);
	UPROPERTY()
	UCompoundableFormalParameter* SOS_EFFECT_TIME = UCompoundableFormalParameter::New<UFloatFormalParameter, float>(UDFStatics::ANCHOR, "Sos effect time", true, 2.0f);
	UPROPERTY()
	USystemInstantiationFormalParameter* SOS_EFFECT_PICKER = UParamUtil::Global<USystemInstantiationFormalParameter, UDFId*>("Child effect", true, UDFStatics::DEFAULT_SYSTEM_ID);
	UPROPERTY()
	UCompoundableFormalParameter* SOS_SHAPE_SCALE = UCompoundableFormalParameter::New<UIntFormalParameter, int>(UDFStatics::ANCHOR, "Shape scale", true, 8000);
	UPROPERTY()
	UColorFormalParameter* SOS_SHAPE_NORMAL = UParamUtil::Global<UColorFormalParameter, FLinearColor>("SOS Shape normal", true, FLinearColor(0, 1.0, 1.0));
	UPROPERTY()
	UBlockFormalParameter* SOS_RING_BLOCK = UParamUtil::Global<UBlockFormalParameter, bool>("Ring settings", true, true);
	UPROPERTY()
	UBlockFormalParameter* SOS_SPHERE_BLOCK = UParamUtil::Global<UBlockFormalParameter, bool>("Sphere settings", true, true);
	UPROPERTY()
	UEnumFormalParameter* SOS_DELAY_TYPE = UParamUtil::Global<UEnumFormalParameter, EnumLikeValue*>("Delay type", true, &EnumLikeValue::SOS_DELAY_FROM_START);
	UPROPERTY()
	UIntFormalParameter* SOS_RECURRING_MAX_NUM = UParamUtil::Global<UIntFormalParameter, int>("Maximum effects", true, 4);

	UPROPERTY()
	UBlockFormalParameter* DISTANCE_CORRECTION_SETTINGS = UParamUtil::Global<UBlockFormalParameter, bool>("Distance correction settings", false, true);
	UPROPERTY()
	UBoolFormalParameter* USE_DISTANCE_CORRECTION = UParamUtil::Global<UBoolFormalParameter, bool>("Use distance correction", true, true);
	UPROPERTY()
	UFloatFormalParameter* DISTANCE_CORRECTION_SCALE = UParamUtil::Global<UFloatFormalParameter, float>("Correction linear scale", true, 1.0f);
	UPROPERTY()
	UFloatFormalParameter* DISTANCE_CORRECTION_EXPONENT = UParamUtil::Global<UFloatFormalParameter, float>("Correction exponent", true, 0.5f);
	UPROPERTY()
	UBlockFormalParameter* DRAG_SETTINGS = UParamUtil::Global<UBlockFormalParameter, bool>("Aerodynamic drag", false, true);
	UPROPERTY()
	UFloatFormalParameter* DRAG_EXPONENT = UParamUtil::Global<UFloatFormalParameter, float>("Drag exponent", true, 0.2f);
	UPROPERTY()
	UFloatFormalParameter* DRAG_LOW_SPEED_SCALE = UParamUtil::Global<UFloatFormalParameter, float>("Drag low speed scale", true, 1.f);
	UPROPERTY()
	UFloatFormalParameter* DRAG_HIGH_SPEED_SCALE = UParamUtil::Global<UFloatFormalParameter, float>("Drag high speed scale", true, 1.f);


	/**
	 * MOTION SETTINGS 
	 */
	UPROPERTY()
	UBlockFormalParameter* MOTION_SETTINGS_BLOCK = UParamUtil::Global<UBlockFormalParameter, bool>("Motion settings", true, true);
	UPROPERTY()
	UEnumFormalParameter* MOTION_TYPE = UParamUtil::Global<UEnumFormalParameter, EnumLikeValue*>("Motion type", true, &EnumLikeValue::NO_MOTION);
	UPROPERTY()
	UFloatFormalParameter* MOTION_START_DELAY = UParamUtil::Global<UFloatFormalParameter, float>("Start delay", true, 0.0);

	UPROPERTY()
	UBlockFormalParameter* FISH_MOTION_BLOCK = UParamUtil::Global<UBlockFormalParameter, bool>("Fish motion", true, true);
	UPROPERTY()
	UFloatFormalParameter* MOTION_FISH_FREQUENCY = UParamUtil::Global<UFloatFormalParameter, float>("Frequency", true, 80.0);
	UPROPERTY()
	UFloatFormalParameter* MOTION_FISH_AMPLITUDE = UParamUtil::Global<UFloatFormalParameter, float>("Amplitude", true, 100.0);

	UPROPERTY()
	UBlockFormalParameter* BEES_MOTION_BLOCK = UParamUtil::Global<UBlockFormalParameter, bool>("Bees motion", true, true);
	UPROPERTY()
	UFloatFormalParameter* MOTION_BEES_ROTATION = UParamUtil::Global<UFloatFormalParameter, float>("Rotation rate", true, 30.0);
	UPROPERTY()
	UFloatFormalParameter* MOTION_BEES_SPEED = UParamUtil::Global<UFloatFormalParameter, float>("Speed", true, 3000.0);

	UPROPERTY()
	UBlockFormalParameter* WHEELS_MOTION_BLOCK = UParamUtil::Global<UBlockFormalParameter, bool>("Wheels motion", true, true);
	UPROPERTY()
	UFloatFormalParameter* MOTION_WHEELS_ROTATION = UParamUtil::Global<UFloatFormalParameter, float>("Rotation rate", true, 30.0);
	UPROPERTY()
	UFloatFormalParameter* MOTION_WHEELS_SPEED = UParamUtil::Global<UFloatFormalParameter, float>("Speed", true, 3000.0);
	UPROPERTY()
	UFloatFormalParameter* MOTION_WHEELS_EJECTION_SPEED = UParamUtil::Global<UFloatFormalParameter, float>("Trail ejection speed", false, 3);

	UPROPERTY()
	UBlockFormalParameter* SPIRAL_MOTION_BLOCK = UParamUtil::Global<UBlockFormalParameter, bool>("Spiral motion", true, true);
	UPROPERTY()
	UFloatFormalParameter* MOTION_SPIRALS_ROTATION = UParamUtil::Global<UFloatFormalParameter, float>("Rotation rate", true, 30.0);
	UPROPERTY()
	UFloatFormalParameter* MOTION_SPIRALS_EJECTION_SPEED = UParamUtil::Global<UFloatFormalParameter, float>("Size", false, 3.0);

	UPROPERTY()
	UBlockFormalParameter* ADVANCED_MOTION_BLOCK = UParamUtil::Global<UBlockFormalParameter, bool>("Advanced motion", true, true);
	UPROPERTY()
	UFloatFormalParameter* MOTION_ROLL_MIN_ROTATION = UParamUtil::Global<UFloatFormalParameter, float>("Roll min rotation rate", true, 30.0);
	UPROPERTY()
	UFloatFormalParameter* MOTION_ROLL_MAX_ROTATION = UParamUtil::Global<UFloatFormalParameter, float>("Roll max rotation rate", true, 60.0);
	UPROPERTY()
	UFloatFormalParameter* MOTION_PITCH_MIN_ROTATION = UParamUtil::Global<UFloatFormalParameter, float>("Pitch min rotation rate", true, 30.0);
	UPROPERTY()
	UFloatFormalParameter* MOTION_PITCH_MAX_ROTATION = UParamUtil::Global<UFloatFormalParameter, float>("Pitch max rotation rate", true, 60.0);
	UPROPERTY()
	UFloatFormalParameter* MOTION_YAW_ROTATION = UParamUtil::Global<UFloatFormalParameter, float>("Yaw rotation rate", true, 60.0);
	UPROPERTY()
	UFloatFormalParameter* MOTION_NORMAL_THRUST = UParamUtil::Global<UFloatFormalParameter, float>("Normal thrust", true, 10000.0);
	UPROPERTY()
	UFloatFormalParameter* MOTION_NORMAL_FREQUENCY = UParamUtil::Global<UFloatFormalParameter, float>("Normal motion frequency", true, 120);
	UPROPERTY()
	UFloatFormalParameter* MOTION_FORWARD_THRUST = UParamUtil::Global<UFloatFormalParameter, float>("Forward thrust", true, 5000);


	/**
	 * TRAIL SETTINGS
	 */
	UPROPERTY()
	UBlockFormalParameter* TRAIL_SETTINGS_BLOCK = UParamUtil::Global<UBlockFormalParameter, bool>("Trails", true, true);
	UPROPERTY()
	UBlockFormalParameter* SMOKE_TRAIL_SETTINGS_BLOCK = UParamUtil::Global<UBlockFormalParameter, bool>("Smoke trail settings", true, true);
	UPROPERTY()
	UBoolFormalParameter* USE_SMOKE_TRAIL = UParamUtil::Global<UBoolFormalParameter, bool>("Use smoke trail", true, false);
	UPROPERTY()
	UFloatFormalParameter* SMOKE_TRAIL_SPREAD = UParamUtil::Global<UFloatFormalParameter, float>("Smoke Trail Spread", true, 0.0f);
	UPROPERTY()
	UFloatFormalParameter* SMOKE_TRAIL_LIFETIME = UParamUtil::Global<UFloatFormalParameter, float>("Smoke Trail Lifetime", true, 3.0f);
	UPROPERTY()
	UFloatFormalParameter* SMOKE_TRAIL_INTENSITY = UParamUtil::Global<UFloatFormalParameter, float>("Smoke Trail Intensity", false, 1.0f);
	UPROPERTY()
	UIntFormalParameter* SMOKE_TRAIL_SPRITE_SIZE = UParamUtil::Global<UIntFormalParameter, int>("Smoke Trail Sprite Size", true, 500);
	UPROPERTY()
	UFloatFormalParameter* SMOKE_TRAIL_EMISSION_DURATION = UParamUtil::Global<UFloatFormalParameter, float>("Smoke Trail Emission Duration", false, 4.0f);
	UPROPERTY()
	UBlockFormalParameter* CRACKLE_TRAIL_SETTINGS_BLOCK = UParamUtil::Global<UBlockFormalParameter, bool>("Crackle trail settings", true, true);
	UPROPERTY()
	UBoolFormalParameter* USE_CRACKLE_TRAIL = UParamUtil::Global<UBoolFormalParameter, bool>("Use crackle trail", true, false);
	UPROPERTY()
	UFloatFormalParameter* CRACKLE_TRAIL_SPREAD = UParamUtil::Global<UFloatFormalParameter, float>("Crackle Trail Spread", false, 1.5f);
	UPROPERTY()
	UFloatFormalParameter* CRACKLE_TRAIL_EJECTION_SPEED = UParamUtil::Global<UFloatFormalParameter, float>("Crackle Trail Ejection Speed", true, 0.0f);
	UPROPERTY()
	UCompoundableFormalParameter* CRACKLE_TRAIL_LIFETIME = UCompoundableFormalParameter::New<UFloatFormalParameter, float>(
		UDFStatics::ANCHOR, "Crackle trail lifetime", true, 0.6f);
	UPROPERTY()
	UFloatFormalParameter* CRACKLE_TRAIL_SPRITE_SIZE = UParamUtil::Global<UFloatFormalParameter, float>("Crackle Trail Sprite Size", false, 4.0f);
	UPROPERTY()
	UIntFormalParameter* CRACKLE_TRAIL_SPAWN_RATE = UParamUtil::Global<UIntFormalParameter, int>("Crackle Trail Spawn Rate", true, 200);
	UPROPERTY()
	UFloatFormalParameter* CRACKLE_TRAIL_EMISSION_DURATION = UParamUtil::Global<UFloatFormalParameter, float>("Crackle Trail Emission Duration", true, 3.0f);

	UPROPERTY()
	UBlockFormalParameter* WILLOW_TRAIL_SETTINGS_BLOCK = UParamUtil::Global<UBlockFormalParameter, bool>("Willow trail settings", true, true);
	UPROPERTY()
	UBoolFormalParameter* USE_WILLOW_TRAIL = UParamUtil::Global<UBoolFormalParameter, bool>("Use willow trail", true, false);
	UPROPERTY()
	UFloatFormalParameter* WILLOW_TRAIL_SPREAD = UParamUtil::Global<UFloatFormalParameter, float>("Willow Trail Spread", false, 0.10f);
	UPROPERTY()
	UFloatFormalParameter* WILLOW_TRAIL_EJECTION_SPEED = UParamUtil::Global<UFloatFormalParameter, float>("Willow Trail Ejection Speed", true, 0.0f);
	UPROPERTY()
	UCompoundableFormalParameter* WILLOW_TRAIL_LIFETIME = UCompoundableFormalParameter::New<UFloatFormalParameter, float>(
		UDFStatics::ANCHOR, "Willow trail lifetime", true, 3.0f, 4.0f);
	UPROPERTY()
	UFloatFormalParameter* WILLOW_TRAIL_SPRITE_SIZE = UParamUtil::Global<UFloatFormalParameter, float>("Willow Trail Sprite Size", false, 35.0f);
	UPROPERTY()
	UIntFormalParameter* WILLOW_TRAIL_SPAWN_RATE = UParamUtil::Global<UIntFormalParameter, int>("Willow Trail Spawn Rate", true, 150);
	UPROPERTY()
	UFloatFormalParameter* WILLOW_TRAIL_EMISSION_DURATION = UParamUtil::Global<UFloatFormalParameter, float>("Willow Trail Emission Duration", true, 5.0f);


	virtual void Initialize() override;

	void AddParameter(UAbstractFormalParameter* Parameter);

	TArray<UAbstractFormalParameter*> GetParameters() const
	{
		return Parameters;
	}

	static UDefaultParameterSystem* Make()
	{
		auto Sys = NewObject<UDefaultParameterSystem>(UDFStatics::ANCHOR);
		Sys->Initialize();
		Sys->SetId(UDFStatics::DEFAULT_SYSTEM_ID);
		Sys->SetDisplayName("Default Aerial Effect");
		return Sys;
	}
	
	virtual TArray<UAbstractFormalParameter*>* GetOuterParameters() override;
	FString GetId();
	FString GetName();
	UTexture2D* GetIcon();
	void SpawnSystem(UEffectSpawnData* Data, AActor* PlayerRef);
};
