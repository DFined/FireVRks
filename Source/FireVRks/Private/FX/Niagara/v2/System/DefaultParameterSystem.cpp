#include "FX/Niagara/v2/System/DefaultParameterSystem.h"

#include <corecrt_math_defines.h>

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "FX/Niagara/Scheduler/CallbackSystemDriver.h"
#include "FX/Niagara/Scheduler/SystemSpawnData.h"
#include "FX/Niagara/v2/ValueEqualsPredicate.h"
#include "FX/Niagara/v2/FormalParameter/EnumFormalParameter.h"
#include "FX/Niagara/v2/ParameterValue/FloatParameterValue.h"
#include "FX/Niagara/v2/ParameterValue/ListParameterValue.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/Icons.h"
#include "DFUI/DFStyleUtil.h"
#include "Util/DFStatics.h"

void UDefaultParameterSystem::Initialize()
{
	if (!IsInit)
	{
		SetDescription("The default aerial effect system. The basis for all the others");
		SetAuthor("#DFined");
		AddParameter(MAIN_SETTINGS_BLOCK);
		{
			MAIN_SETTINGS_BLOCK->Add(EFFECT_SHAPE);

			MAIN_SETTINGS_BLOCK->Add(CONE_SETTINGS_BLOCK);
			{
				CONE_SETTINGS_BLOCK->SetPredicate(new ValueEqualsPredicate<ENUM_VALUE>(EFFECT_SHAPE, &EnumLikeValue::CONE));
				CONE_SETTINGS_BLOCK->Add(CONE_SURFACE_ONLY);
				CONE_SETTINGS_BLOCK->Add(CONE_ANGLE);
				CONE_SETTINGS_BLOCK->Add(CONE_ANGLE_VARIANCE);
				CONE_ANGLE_VARIANCE->SetPredicate(new ValueEqualsPredicate<BOOL_VALUE>(CONE_SURFACE_ONLY, true));
				CONE_SETTINGS_BLOCK->Add(CONE_UNIFORM);
				CONE_SETTINGS_BLOCK->Add(CONE_BI_DIRECTIONAL);
			}

			MAIN_SETTINGS_BLOCK->Add(CLUSTER_SIZE);
			MAIN_SETTINGS_BLOCK->Add(CLUSTER_SPACING);

			MAIN_SETTINGS_BLOCK->Add(SPRITE_COUNT);
			MAIN_SETTINGS_BLOCK->Add(VELOCITY->GetBlockParam());

			MAIN_SETTINGS_BLOCK->Add(USE_SECOND_COLOR);
			MAIN_SETTINGS_BLOCK->Add(MAIN_COLOR);
			MAIN_SETTINGS_BLOCK->Add(SECONDARY_COLOR);
			SECONDARY_COLOR->SetPredicate(new ValueEqualsPredicate<BOOL_VALUE>(USE_SECOND_COLOR, true));

			MAIN_SETTINGS_BLOCK->Add(LIFETIME->GetBlockParam());
			MAIN_SETTINGS_BLOCK->Add(SPRITE_SIZE->GetBlockParam());
			MAIN_SETTINGS_BLOCK->Add(EFFECT_ROTATION_TYPE);
			MAIN_SETTINGS_BLOCK->Add(NORMAL_VECTOR);
			NORMAL_VECTOR->SetPredicate(new ValueEqualsPredicate<ENUM_VALUE>(EFFECT_ROTATION_TYPE, &EnumLikeValue::FIXED));

			MAIN_SETTINGS_BLOCK->Add(TRAIL_SETTINGS_BLOCK);
			{
				TRAIL_SETTINGS_BLOCK->Add(SMOKE_TRAIL_SETTINGS_BLOCK);
				{
					SMOKE_TRAIL_SETTINGS_BLOCK->Add(USE_SMOKE_TRAIL);
					SMOKE_TRAIL_SETTINGS_BLOCK->Add(SMOKE_TRAIL_LIFETIME);
					SMOKE_TRAIL_SETTINGS_BLOCK->Add(SMOKE_TRAIL_SPREAD);
					SMOKE_TRAIL_SETTINGS_BLOCK->Add(SMOKE_TRAIL_EMISSION_DURATION);
					SMOKE_TRAIL_SETTINGS_BLOCK->Add(SMOKE_TRAIL_SPRITE_SIZE);
					SMOKE_TRAIL_SETTINGS_BLOCK->Add(SMOKE_TRAIL_INTENSITY);
				}

				TRAIL_SETTINGS_BLOCK->Add(WILLOW_TRAIL_SETTINGS_BLOCK);
				{
					WILLOW_TRAIL_SETTINGS_BLOCK->Add(USE_WILLOW_TRAIL);
					WILLOW_TRAIL_SETTINGS_BLOCK->Add(WILLOW_TRAIL_SPREAD);
					WILLOW_TRAIL_SETTINGS_BLOCK->Add(WILLOW_TRAIL_SPAWN_RATE);
					WILLOW_TRAIL_SETTINGS_BLOCK->Add(WILLOW_TRAIL_SPRITE_SIZE);
					WILLOW_TRAIL_SETTINGS_BLOCK->Add(WILLOW_TRAIL_EMISSION_DURATION);
					WILLOW_TRAIL_SETTINGS_BLOCK->Add(WILLOW_TRAIL_LIFETIME->GetBlockParam());
					WILLOW_TRAIL_SETTINGS_BLOCK->Add(WILLOW_TRAIL_EJECTION_SPEED);
				}

				TRAIL_SETTINGS_BLOCK->Add(CRACKLE_TRAIL_SETTINGS_BLOCK);
				{
					CRACKLE_TRAIL_SETTINGS_BLOCK->Add(USE_CRACKLE_TRAIL);
					CRACKLE_TRAIL_SETTINGS_BLOCK->Add(CRACKLE_TRAIL_SPREAD);
					CRACKLE_TRAIL_SETTINGS_BLOCK->Add(CRACKLE_TRAIL_SPAWN_RATE);
					CRACKLE_TRAIL_SETTINGS_BLOCK->Add(CRACKLE_TRAIL_SPRITE_SIZE);
					CRACKLE_TRAIL_SETTINGS_BLOCK->Add(CRACKLE_TRAIL_EMISSION_DURATION);
					CRACKLE_TRAIL_SETTINGS_BLOCK->Add(CRACKLE_TRAIL_LIFETIME->GetBlockParam());
					CRACKLE_TRAIL_SETTINGS_BLOCK->Add(CRACKLE_TRAIL_EJECTION_SPEED);
				}
			}
			MAIN_SETTINGS_BLOCK->Add(COLOR_EFFECT_SETTINGS);
			{
				COLOR_EFFECT_SETTINGS->Add(COLOR_EFFECT_TYPE);

				COLOR_EFFECT_SETTINGS->Add(SIMPLE_COLOR_CHANGE_BLOCK);
				{
					SIMPLE_COLOR_CHANGE_BLOCK->SetPredicate(
						new ValueEqualsPredicate<ENUM_VALUE>(COLOR_EFFECT_TYPE, &EnumLikeValue::SIMPLE_COLOR_CHANGE));
					SIMPLE_COLOR_CHANGE_BLOCK->Add(LERP_START_TIME);
					SIMPLE_COLOR_CHANGE_BLOCK->Add(LERP_END_TIME);
					SIMPLE_COLOR_CHANGE_BLOCK->Add(TARGET_COLOR);
				}

				COLOR_EFFECT_SETTINGS->Add(COLOR_FLARE_BLOCK);
				{
					COLOR_FLARE_BLOCK->SetPredicate(new ValueEqualsPredicate<ENUM_VALUE>(COLOR_EFFECT_TYPE, &EnumLikeValue::FLARE));
					COLOR_FLARE_BLOCK->Add(LERP_START_TIME);
					COLOR_FLARE_BLOCK->Add(LERP_END_TIME);
					COLOR_FLARE_BLOCK->Add(TARGET_COLOR);
				}

				COLOR_EFFECT_SETTINGS->Add(COLOR_FLICKER_BLOCK);
				{
					COLOR_FLICKER_BLOCK->SetPredicate(new ValueEqualsPredicate<ENUM_VALUE>(COLOR_EFFECT_TYPE, &EnumLikeValue::FLICKER));
					COLOR_FLICKER_BLOCK->Add(LERP_START_TIME);
					COLOR_FLICKER_BLOCK->Add(LERP_END_TIME);
					COLOR_FLICKER_BLOCK->Add(TARGET_COLOR);
				}

				COLOR_EFFECT_SETTINGS->Add(COLOR_WAVE_BLOCK);
				{
					COLOR_WAVE_BLOCK->SetPredicate(new ValueEqualsPredicate<ENUM_VALUE>(COLOR_EFFECT_TYPE, &EnumLikeValue::COLOR_WAVE));
					COLOR_WAVE_BLOCK->Add(LERP_START_TIME);
					COLOR_WAVE_BLOCK->Add(LERP_END_TIME);
					COLOR_WAVE_BLOCK->Add(TARGET_COLOR);
					COLOR_WAVE_BLOCK->Add(WAVE_CYCLE_PERCENT);
				}

				COLOR_EFFECT_SETTINGS->Add(ADVANCE_COLOR_LERP_BLOCK);
				{
					ADVANCE_COLOR_LERP_BLOCK->SetPredicate(new ValueEqualsPredicate<ENUM_VALUE>(COLOR_EFFECT_TYPE, &EnumLikeValue::ADVANCED_COLOR_LERP));
					ADVANCE_COLOR_LERP_BLOCK->Add(TARGET_COLOR);
					ADVANCE_COLOR_LERP_BLOCK->Add(LERP_START_TIME);
					ADVANCE_COLOR_LERP_BLOCK->Add(LERP_END_TIME);
					ADVANCE_COLOR_LERP_BLOCK->Add(LERP_FREQUENCY);
					ADVANCE_COLOR_LERP_BLOCK->Add(LERP_PHASE_COUNT);
					ADVANCE_COLOR_LERP_BLOCK->Add(LERP_WAVE_DUTY_CYCLE);
				}
			}
		}
		//MOTION
		MAIN_SETTINGS_BLOCK->Add(MOTION_SETTINGS_BLOCK);
		MOTION_SETTINGS_BLOCK->Add(MOTION_START_DELAY);
		MOTION_SETTINGS_BLOCK->Add(MOTION_TYPE);

		MOTION_SETTINGS_BLOCK->Add(FISH_MOTION_BLOCK);
		{
			FISH_MOTION_BLOCK->SetPredicate(new ValueEqualsPredicate<ENUM_VALUE>(MOTION_TYPE, &EnumLikeValue::FISH));
			FISH_MOTION_BLOCK->Add(MOTION_FISH_FREQUENCY);
			FISH_MOTION_BLOCK->Add(MOTION_FISH_AMPLITUDE);
		}

		MOTION_SETTINGS_BLOCK->Add(BEES_MOTION_BLOCK);
		{
			BEES_MOTION_BLOCK->SetPredicate(new ValueEqualsPredicate<ENUM_VALUE>(MOTION_TYPE, &EnumLikeValue::BEES));
			BEES_MOTION_BLOCK->Add(MOTION_BEES_ROTATION);
			BEES_MOTION_BLOCK->Add(MOTION_BEES_SPEED);
		}

		MOTION_SETTINGS_BLOCK->Add(WHEELS_MOTION_BLOCK);
		{
			WHEELS_MOTION_BLOCK->SetPredicate(new ValueEqualsPredicate<ENUM_VALUE>(MOTION_TYPE, &EnumLikeValue::WHEELS));
			WHEELS_MOTION_BLOCK->Add(MOTION_WHEELS_ROTATION);
			WHEELS_MOTION_BLOCK->Add(MOTION_WHEELS_SPEED);
			WHEELS_MOTION_BLOCK->Add(MOTION_WHEELS_EJECTION_SPEED);
		}

		MOTION_SETTINGS_BLOCK->Add(SPIRAL_MOTION_BLOCK);
		{
			SPIRAL_MOTION_BLOCK->SetPredicate(new ValueEqualsPredicate<ENUM_VALUE>(MOTION_TYPE, &EnumLikeValue::SPIRALS));
			SPIRAL_MOTION_BLOCK->Add(MOTION_SPIRALS_ROTATION);
			SPIRAL_MOTION_BLOCK->Add(MOTION_SPIRALS_EJECTION_SPEED);
		}

		MOTION_SETTINGS_BLOCK->Add(ADVANCED_MOTION_BLOCK);
		{
			ADVANCED_MOTION_BLOCK->SetPredicate(new ValueEqualsPredicate<ENUM_VALUE>(MOTION_TYPE, &EnumLikeValue::ADVANCED));
			ADVANCED_MOTION_BLOCK->Add(MOTION_ROLL_MIN_ROTATION);
			ADVANCED_MOTION_BLOCK->Add(MOTION_ROLL_MAX_ROTATION);
			ADVANCED_MOTION_BLOCK->Add(MOTION_PITCH_MIN_ROTATION);
			ADVANCED_MOTION_BLOCK->Add(MOTION_PITCH_MAX_ROTATION);
			ADVANCED_MOTION_BLOCK->Add(MOTION_YAW_ROTATION);
			ADVANCED_MOTION_BLOCK->Add(MOTION_FORWARD_THRUST);
			ADVANCED_MOTION_BLOCK->Add(MOTION_NORMAL_THRUST);
			ADVANCED_MOTION_BLOCK->Add(MOTION_NORMAL_FREQUENCY);
			ADVANCED_MOTION_BLOCK->Add(MOTION_FORWARD_THRUST);
		}


		/**
		 * Compound effect setup
		 */
		MAIN_SETTINGS_BLOCK->Add(SOS_CONFIGS_LIST);

		SOS_CONFIG_BLOCK->Add(SOS_CHILD_SHELLS_NUM);
		SOS_CONFIG_BLOCK->Add(SOS_EFFECT_TIME->GetBlockParam());
		SOS_CONFIG_BLOCK->Add(SOS_EFFECT_SHAPE);
		SOS_CONFIG_BLOCK->Add(SOS_DELAY_TYPE);
		SOS_DELAY_TYPE->SetPredicate(new ValueEqualsPredicate<ENUM_VALUE>(SOS_EFFECT_SHAPE, &EnumLikeValue::SOS_FROM_PARENT_PARTICLES));
		SOS_CONFIG_BLOCK->Add(SOS_RECURRING_MAX_NUM);
		SOS_RECURRING_MAX_NUM->SetPredicate(new ValueEqualsPredicate<ENUM_VALUE>(SOS_DELAY_TYPE, &EnumLikeValue::SOS_DELAY_AT_REGULAR_INTERVAL));

		SOS_CONFIG_BLOCK->Add(SOS_SPHERE_BLOCK);
		SOS_SPHERE_BLOCK->SetPredicate(new ValueEqualsPredicate<ENUM_VALUE>(SOS_EFFECT_SHAPE, &EnumLikeValue::SOS_SPHERE));
		SOS_SPHERE_BLOCK->Add(SOS_SHAPE_SCALE->GetBlockParam());


		SOS_CONFIG_BLOCK->Add(SOS_RING_BLOCK);
		SOS_RING_BLOCK->SetPredicate(new ValueEqualsPredicate<ENUM_VALUE>(SOS_EFFECT_SHAPE, &EnumLikeValue::SOS_RING));
		SOS_RING_BLOCK->Add(SOS_SHAPE_SCALE->GetBlockParam());
		SOS_RING_BLOCK->Add(SOS_SHAPE_NORMAL);

		SOS_CONFIG_BLOCK->Add(SOS_EFFECT_PICKER);



		//TECHNICAL PARAMETERS
		MAIN_SETTINGS_BLOCK->Add(DISTANCE_CORRECTION_SETTINGS);
		DISTANCE_CORRECTION_SETTINGS->SetPredicate(new ValueEqualsPredicate<BOOL_VALUE>(USE_DISTANCE_CORRECTION, true));
		DISTANCE_CORRECTION_SETTINGS->Add(USE_DISTANCE_CORRECTION);
		DISTANCE_CORRECTION_SETTINGS->Add(DISTANCE_CORRECTION_SCALE);
		DISTANCE_CORRECTION_SETTINGS->Add(DISTANCE_CORRECTION_EXPONENT);

		MAIN_SETTINGS_BLOCK->Add(DRAG_SETTINGS);
		DRAG_SETTINGS->Add(DRAG_EXPONENT);
		DRAG_SETTINGS->Add(DRAG_LOW_SPEED_SCALE);
		DRAG_SETTINGS->Add(DRAG_HIGH_SPEED_SCALE);

		IsInit = true;
	}
}

void UDefaultParameterSystem::AddParameter(UAbstractFormalParameter* Parameter)
{
	Parameters.Add(Parameter->GetId(), Parameter);
}

TMap<UDFId*, UAbstractFormalParameter*>* UDefaultParameterSystem::GetOuterParameters()
{
	return &Parameters;
}

void UDefaultParameterSystem::GetOuterParametersInOrder(TArray<UAbstractFormalParameter*>& Result)
{
	DFU::GetValues(*GetOuterParameters(), Result);
}

FString UDefaultParameterSystem::GetId()
{
	return "_Internal_.DEFAULT_EFFECT";
}

FString UDefaultParameterSystem::GetName()
{
	return "Default System";
}

UIcon* UDefaultParameterSystem::GetIcon()
{
	return UDFStatics::ICONS->DEFAULT_EFFECT_ICON;
}


void UDefaultParameterSystem::SpawnSystem(USystemSpawnData* Data)
{
	auto Context = Data->GetContext();

	auto Location = Data->GetLocation();

	
	auto Distance = FMath::Max(Location.Distance(Location, UDFStatics::GetPlayerCamera()->GetComponentLocation()), 1000);

	auto Effect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(Data->GetWorldObject(), UDFStatics::DEFAULT_SYSTEM, Location);

	auto RotationType = EFFECT_ROTATION_TYPE->GetValue(Context);

	FVector Normal;
	switch (RotationType->GetOrdinal())
	{
		default:
		case 0: Normal = FVector(NORMAL_VECTOR->GetValue(Context));
			break;
		case 1:
			{
				Normal = Data->GetUpwardVector();
				break;
			}
		case 2:
			{
				Normal = UKismetMathLibrary::RandomUnitVector();
				break;
			}
	}
	Effect->SetVectorParameter("PlaneNormal", Normal);

	//Actually transfer all the settings to the system
	Effect->SetIntParameter("SpriteSizeMin", SPRITE_SIZE->GetMin<INT_VALUE>(Context));
	Effect->SetIntParameter("SpriteSizeMax", SPRITE_SIZE->GetMax<INT_VALUE>(Context));

	Effect->SetFloatParameter("StarsLifetimeMin", LIFETIME->GetMin<FLOAT_VALUE>(Context));
	Effect->SetFloatParameter("StarsLifetimeMax", LIFETIME->GetMax<FLOAT_VALUE>(Context));

	Effect->SetIntParameter("InitialVelocityMin", VELOCITY->GetMin<INT_VALUE>(Context));
	Effect->SetIntParameter("InitialVelocityMax", VELOCITY->GetMax<INT_VALUE>(Context));

	Effect->SetColorParameter("Color1", MAIN_COLOR->GetValue(Context));
	Effect->SetColorParameter("Color2", USE_SECOND_COLOR->GetValue(Context) ? SECONDARY_COLOR->GetValue(Context) : MAIN_COLOR->GetValue(Context));

	Effect->SetIntParameter("StarsCount", SPRITE_COUNT->GetValue(Context));


	//TRAILS
	Effect->SetBoolParameter("EnableSmokeTrails", USE_SMOKE_TRAIL->GetValue(Context));
	Effect->SetFloatParameter("SmokeTrailSpread", SMOKE_TRAIL_SPREAD->GetValue(Context));
	Effect->SetFloatParameter("SmokeTrailLifetime", SMOKE_TRAIL_LIFETIME->GetValue(Context));
	Effect->SetFloatParameter("SmokeTrailIntensity", SMOKE_TRAIL_INTENSITY->GetValue(Context));
	Effect->SetFloatParameter("SmokeTrailSpriteSize", SMOKE_TRAIL_SPRITE_SIZE->GetValue(Context));
	Effect->SetFloatParameter("SmokeTrailEmissionDuration", SMOKE_TRAIL_EMISSION_DURATION->GetValue(Context));

	Effect->SetBoolParameter("EnableCrackleTrails", USE_CRACKLE_TRAIL->GetValue(Context));
	Effect->SetFloatParameter("CrackleTrailSpread", CRACKLE_TRAIL_SPREAD->GetValue(Context));
	Effect->SetFloatParameter("CrackleTrailEjectionSpeed", CRACKLE_TRAIL_EJECTION_SPEED->GetValue(Context));
	Effect->SetFloatParameter("CrackleTrailMaxLifetime", CRACKLE_TRAIL_LIFETIME->GetMax<FLOAT_VALUE>(Context));
	Effect->SetFloatParameter("CrackleTrailMinLifetime", CRACKLE_TRAIL_LIFETIME->GetMin<FLOAT_VALUE>(Context));
	Effect->SetFloatParameter("CrackleTrailSpriteSize", CRACKLE_TRAIL_SPRITE_SIZE->GetValue(Context));
	Effect->SetFloatParameter("CrackleTrailSpawnRate", CRACKLE_TRAIL_SPAWN_RATE->GetValue(Context));
	Effect->SetFloatParameter("CrackleTrailEmissionDuration", CRACKLE_TRAIL_EMISSION_DURATION->GetValue(Context));


	Effect->SetBoolParameter("EnableWillowTrails", USE_WILLOW_TRAIL->GetValue(Context));
	Effect->SetFloatParameter("WillowTrailSpread", WILLOW_TRAIL_SPREAD->GetValue(Context));
	Effect->SetFloatParameter("WillowTrailEjectionSpeed", WILLOW_TRAIL_EJECTION_SPEED->GetValue(Context));
	Effect->SetFloatParameter("WillowTrailMaxLifetime", WILLOW_TRAIL_LIFETIME->GetMax<FLOAT_VALUE>(Context));
	Effect->SetFloatParameter("WillowTrailMinLifetime", WILLOW_TRAIL_LIFETIME->GetMin<FLOAT_VALUE>(Context));
	Effect->SetFloatParameter("WillowTrailSpriteSize", WILLOW_TRAIL_SPRITE_SIZE->GetValue(Context));
	Effect->SetFloatParameter("WillowTrailSpawnRate", WILLOW_TRAIL_SPAWN_RATE->GetValue(Context));
	Effect->SetFloatParameter("WillowTrailEmissionDuration", WILLOW_TRAIL_EMISSION_DURATION->GetValue(Context));
	//--------


	Effect->SetFloatParameter("SimpleColorLerpStart", LERP_START_TIME->GetValue(Context));
	Effect->SetFloatParameter("SimpleColorLerpEnd", LERP_END_TIME->GetValue(Context));
	Effect->SetColorParameter("Color3", TARGET_COLOR->GetValue(Context));
	if (COLOR_EFFECT_TYPE->GetValue(Context) == &EnumLikeValue::NO_EFFECT)
	{
		Effect->SetBoolParameter("UseSimpleColorLerp", false);
	}
	else if (COLOR_EFFECT_TYPE->GetValue(Context) == &EnumLikeValue::SIMPLE_COLOR_CHANGE)
	{
		Effect->SetBoolParameter("UseSimpleColorLerp", true);
		Effect->SetFloatParameter("SimpleLerpFrequency", 1.0f);
		Effect->SetIntParameter("ColorLerpPhaseCount", 1);
		Effect->SetFloatParameter("PhaseOverlapFraction", 0.0f);
	}
	else if (COLOR_EFFECT_TYPE->GetValue(Context) == &EnumLikeValue::FLARE)
	{
		Effect->SetBoolParameter("UseSimpleColorLerp", true);
		Effect->SetFloatParameter("SimpleLerpFrequency", 2.0f);
		Effect->SetIntParameter("ColorLerpPhaseCount", COLOR_FLARE_GROUP_COUNT->GetValue(Context));
		Effect->SetFloatParameter("PhaseOverlapFraction", 0.0f);
	}
	else if (COLOR_EFFECT_TYPE->GetValue(Context) == &EnumLikeValue::FLICKER)
	{
		Effect->SetBoolParameter("UseSimpleColorLerp", true);
		Effect->SetFloatParameter("SimpleLerpFrequency", 2.0f);
		Effect->SetIntParameter("ColorLerpPhaseCount", SPRITE_COUNT->GetValue(Context));
		Effect->SetBoolParameter("RandomizeParticleOrder", true);
		Effect->SetFloatParameter("PhaseOverlapFraction", 0.8f);
	}
	else if (COLOR_EFFECT_TYPE->GetValue(Context) == &EnumLikeValue::COLOR_WAVE)
	{
		Effect->SetBoolParameter("UseSimpleColorLerp", true);
		Effect->SetFloatParameter("SimpleLerpFrequency", 2.0f);
		Effect->SetIntParameter("ColorLerpPhaseCount", SPRITE_COUNT->GetValue(Context));
		Effect->SetBoolParameter("RandomizeParticleOrder", false);
		Effect->SetFloatParameter("PhaseOverlapFraction", 0.9f + WAVE_CYCLE_PERCENT->GetValue(Context) / 1000.f);
	}
	else if (COLOR_EFFECT_TYPE->GetValue(Context) == &EnumLikeValue::ADVANCED_COLOR_LERP)
	{
		Effect->SetBoolParameter("UseSimpleColorLerp", true);
		Effect->SetFloatParameter("SimpleLerpFrequency", LERP_FREQUENCY->GetValue(Context));
		Effect->SetIntParameter("ColorLerpPhaseCount", LERP_PHASE_COUNT->GetValue(Context));
		Effect->SetFloatParameter("PhaseOverlapFraction", LERP_WAVE_DUTY_CYCLE->GetValue(Context));
	}
	Effect->SetIntParameter("ShapeType", EFFECT_SHAPE->GetValue(Context)->GetOrdinal());

	Effect->SetIntParameter("ClusterSize", CLUSTER_SIZE->GetValue(Context));
	Effect->SetFloatParameter("ClusterSpacing", CLUSTER_SPACING->GetValue(Context));
	Effect->SetIntParameter("ConeAngle", CONE_ANGLE->GetValue(Context));
	Effect->SetIntParameter("ConeAngleVariance", CONE_ANGLE_VARIANCE->GetValue(Context));
	Effect->SetBoolParameter("ConeSurfaceOnly", CONE_SURFACE_ONLY->GetValue(Context));
	Effect->SetBoolParameter("ConeUniform", CONE_UNIFORM->GetValue(Context));
	Effect->SetBoolParameter("ConeBiDirectional", CONE_BI_DIRECTIONAL->GetValue(Context));


	//TECHNICAL SETTINGS
	Effect->SetBoolParameter("UseDistanceCorrection", USE_DISTANCE_CORRECTION->GetValue(Context));
	Effect->SetFloatParameter("DistanceCorrectionExponent", DISTANCE_CORRECTION_EXPONENT->GetValue(Context));
	Effect->SetFloatParameter("DistanceCorrectionLinearScale", DISTANCE_CORRECTION_SCALE->GetValue(Context));

	Effect->SetFloatParameter("DragExponent", DRAG_EXPONENT->GetValue(Context));
	Effect->SetFloatParameter("LowSpeedDragScale", DRAG_LOW_SPEED_SCALE->GetValue(Context));
	Effect->SetFloatParameter("HighSpeedDragScale", DRAG_HIGH_SPEED_SCALE->GetValue(Context));
	Effect->SetFloatParameter("Distance", Distance);


	//SOS Spawning
	//SOS-subsystem contexts are stored in the list parameter value; Inside each, the SystemInstantiationParameter stores the actual sub-instance-context
	auto SosBlocks = UParamUtil::GetTypedValue<UListParameterValue, TArray<UParameterValueContext*>>(Context->Get(SOS_CONFIGS_LIST));
	if (!SosBlocks.IsEmpty())
	{
		ACallbackSystemDriver* Handler = nullptr;

		// for (UParameterValueContext* SOSContext : SosBlocks)
		// {
			// auto StartTime = SOS_EFFECT_TIME->GetMin<FLOAT_VALUE>(SOSContext);
			// auto EndTime = SOS_EFFECT_TIME->GetMax<FLOAT_VALUE>(SOSContext);
			// auto ChildEffectsNum = SOS_CHILD_SHELLS_NUM->GetValue(SOSContext);
			//
			//
			// auto World = GEngine->GetWorldFromContextObject(Effect, EGetWorldErrorMode::ReturnNull);
			//
			// auto SosShape = SOS_EFFECT_SHAPE->GetValue(SOSContext);
			//
			// auto SystemInstanceParams = Cast<USystemInstantiationParameterValue>(SOSContext->Get(SOS_EFFECT_PICKER));
			//
			// if (SosShape == &EnumLikeValue::SOS_FROM_PARENT_PARTICLES)
			// {
			// 	if (Handler == nullptr)
			// 	{
			// 		Handler = World->SpawnActor<ACallbackSystemDriver>(FVector(Location), FRotator());
			// 		Handler->SetActorTickEnabled(true);
			// 		Handler->Init(SPRITE_COUNT->GetValue(Context), LIFETIME->GetMax<UFloatParameterValue, float>(Context), Effect);
			// 	}
			//
			// 	auto SpawnData = ULaunchSettings::Make(
			// 		Data->GetWorldObject(),
			// 		UEffectSystemManager::GetInstance()->Get (SystemInstanceParams->GetSystem()),
			// 		SystemInstanceParams->GetContext(),
			// 		Data->GetSpawnTarget(),
			// 		0,
			// 		FVector(),
			// 		Normal
			// 	);
			// 	Handler->AddSpawnInfo(
			// 		SpawnData,
			// 		SOS_EFFECT_TIME->GetMin<FLOAT_VALUE>(SOSContext),
			// 		SOS_EFFECT_TIME->GetMax<FLOAT_VALUE>(SOSContext),
			// 		SOS_CHILD_SHELLS_NUM->GetValue(SOSContext),
			// 		SOS_DELAY_TYPE->GetValue(SOSContext),
			// 		SOS_RECURRING_MAX_NUM->GetValue(SOSContext)
			// 	);
			// }
			// else
			// {
			// 	for (int i = 0; i < ChildEffectsNum; i++)
			// 	{
			// 		auto SpawnDelay = FMath::RandRange(StartTime, EndTime);
			//
			//
			// 		int Scale = FMath::RandRange(SOS_SHAPE_SCALE->GetMin<FLOAT_VALUE>(SOSContext), SOS_SHAPE_SCALE->GetMax<FLOAT_VALUE>(SOSContext));
			// 		FVector Offset;
			//
			// 		switch (SosShape->GetOrdinal())
			// 		{
			// 			case 1: Offset = FMath::VRand() * Scale;
			// 				break;
			// 			case 2:
			// 				{
			// 					auto Quat = UKismetMathLibrary::Quat_FindBetweenVectors(
			// 						FVector(0, 1, 0), FVector(SOS_SHAPE_NORMAL->GetValue(SOSContext))
			// 					);
			// 					float Phase = (M_PI * 2 * i) / ChildEffectsNum;
			// 					FVector Rad = (FVector(1, 0, 0) * FMath::Sin(Phase) + FVector(0, 0, 1) * FMath::Cos(Phase));
			// 					Offset = Quat.RotateVector(Rad) * Scale;
			// 				}
			//
			// 			default: break;
			// 		}

					// UDFStatics::EFFECT_SYSTEM_SCHEDULER->ScheduleSpawn(
					// 	new EffectSpawnData(
					// 		SystemInstanceParams->GetSystem(), SystemInstanceParams->GetContext(), Data->GetSpawnTarget(), SpawnDelay, Offset)
					// );
		// 		}
		// 	}
		// }
		// if (Handler != nullptr)
		// {
		// 	Handler->Finalize();
		// 	//TODO Fix memory leak here
		// }
	}


	//MOTION BLOCK
	Effect->SetFloatParameter("ThrustStartDelay", MOTION_START_DELAY->GetValue(Context));
	float MinRoll = 0.0;
	float MaxRoll = 0.0;
	float MinPitch = 0.0;
	float MaxPitch = 0.0;
	float Yaw = 0.0;
	float NormalThrust = 0;
	float NormalFrequency = 0;
	float ForwardThrust = 0;

	switch (MOTION_TYPE->GetValue(Context)->GetOrdinal())
	{
		case 1: //FISH
			{
				NormalFrequency = MOTION_FISH_FREQUENCY->GetValue(Context);
				NormalThrust = MOTION_FISH_AMPLITUDE->GetValue(Context) * 100;
				break;
			}
		case 2: //BEES
			{
				auto omega = MOTION_BEES_ROTATION->GetValue(Context);
				MinRoll = 0.5 * omega;
				MaxRoll = omega;
				MinPitch = MinRoll;
				MaxPitch = MaxRoll;
				Yaw = MinRoll;
				ForwardThrust = MOTION_BEES_SPEED->GetValue(Context);
				break;
			}
		case 3: //WHEELS
			{
				auto omega = MOTION_BEES_ROTATION->GetValue(Context);
				MinRoll = 0.5 * omega;
				MaxRoll = omega;
				MinPitch = MinRoll;
				MaxPitch = MaxRoll;
				Yaw = MinRoll;
				ForwardThrust = MOTION_BEES_SPEED->GetValue(Context);
				Effect->SetFloatParameter("WillowTrailEjectionSpeed", MOTION_WHEELS_EJECTION_SPEED->GetValue(Context));
				Effect->SetFloatParameter("CrackleTrailEjectionSpeed", MOTION_WHEELS_EJECTION_SPEED->GetValue(Context));
				break;
			}
		case 4: //SPIRALS
			{
				Yaw = MOTION_SPIRALS_ROTATION->GetValue(Context);
				Effect->SetFloatParameter("WillowTrailEjectionSpeed", MOTION_SPIRALS_EJECTION_SPEED->GetValue(Context));
				Effect->SetFloatParameter("CrackleTrailEjectionSpeed", MOTION_SPIRALS_EJECTION_SPEED->GetValue(Context));
				break;
			}
		case 5: //ADVANCED
			{
				MinRoll = MOTION_ROLL_MIN_ROTATION->GetValue(Context);
				MaxRoll = MOTION_ROLL_MAX_ROTATION->GetValue(Context);
				MinPitch = MOTION_PITCH_MIN_ROTATION->GetValue(Context);
				MaxPitch = MOTION_PITCH_MAX_ROTATION->GetValue(Context);
				Yaw = MOTION_YAW_ROTATION->GetValue(Context);
				NormalThrust = MOTION_NORMAL_THRUST->GetValue(Context);
				NormalFrequency = MOTION_NORMAL_FREQUENCY->GetValue(Context);
				ForwardThrust = MOTION_FORWARD_THRUST->GetValue(Context);
			}
	}

	Effect->SetFloatParameter("RollMinRotationRate", MinRoll);
	Effect->SetFloatParameter("RollMaxRotationRate", MaxRoll);
	Effect->SetFloatParameter("PitchMinRotationRate", MinPitch);
	Effect->SetFloatParameter("PitchMaxRotationRate", MaxPitch);
	Effect->SetFloatParameter("YawRotationRate", Yaw);
	Effect->SetFloatParameter("NormalThrust", NormalThrust);
	Effect->SetFloatParameter("NormalMotionFrequency", NormalFrequency);
	Effect->SetFloatParameter("StarsThrust", ForwardThrust);
	
}
