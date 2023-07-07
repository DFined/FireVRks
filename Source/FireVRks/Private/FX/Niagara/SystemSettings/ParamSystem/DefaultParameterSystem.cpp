#include "FX/Niagara/System/DefaultParameterSystem.h"

#include <corecrt_math_defines.h>

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "FX/Niagara/Scheduler/CallbackSystemDriver.h"
#include "FX/Niagara/Scheduler/EffectSystemScheduler.h"
#include "FX/Niagara/SystemSettings/FormalParameter/ValueEqualsPredicate.h"
#include "FX/Niagara/SystemSettings/ParameterValues/SystemInstantiationParameterValue.h"
#include "Kismet/KismetMathLibrary.h"

void UDefaultParameterSystem::Initialize()
{
	if (!IsInit)
	{
		AddParameter(&MAIN_SETTINGS_BLOCK);
		{
			MAIN_SETTINGS_BLOCK.AddChild(&EFFECT_SHAPE);

			MAIN_SETTINGS_BLOCK.AddChild(&CONE_SETTINGS_BLOCK);
			{
				CONE_SETTINGS_BLOCK.SetDisplayPredicate(ValueEqualsPredicate<EnumLikeValue*>::Of(&EFFECT_SHAPE, &EnumLikeValue::CONE));
				CONE_SETTINGS_BLOCK.AddChild(&CONE_SURFACE_ONLY);
				CONE_SETTINGS_BLOCK.AddChild(&CONE_ANGLE);
				CONE_SETTINGS_BLOCK.AddChild(&CONE_ANGLE_VARIANCE);
				CONE_ANGLE_VARIANCE.SetDisplayPredicate(ValueEqualsPredicate<bool>::Of(&CONE_SURFACE_ONLY, true));
				CONE_SETTINGS_BLOCK.AddChild(&CONE_UNIFORM);
				CONE_SETTINGS_BLOCK.AddChild(&CONE_BI_DIRECTIONAL);
			}

			MAIN_SETTINGS_BLOCK.AddChild(&CLUSTER_SIZE);
			MAIN_SETTINGS_BLOCK.AddChild(&CLUSTER_SPACING);

			MAIN_SETTINGS_BLOCK.AddChild(&SPRITE_COUNT);
			MAIN_SETTINGS_BLOCK.AddChild(VELOCITY.GetBlockParam());

			MAIN_SETTINGS_BLOCK.AddChild(&USE_SECOND_COLOR);
			MAIN_SETTINGS_BLOCK.AddChild(&MAIN_COLOR);
			MAIN_SETTINGS_BLOCK.AddChild(&SECONDARY_COLOR);
			SECONDARY_COLOR.SetDisplayPredicate(ValueEqualsPredicate<bool>::Of(&USE_SECOND_COLOR, true));

			MAIN_SETTINGS_BLOCK.AddChild(LIFETIME.GetBlockParam());
			MAIN_SETTINGS_BLOCK.AddChild(SPRITE_SIZE.GetBlockParam());
			MAIN_SETTINGS_BLOCK.AddChild(&EFFECT_ROTATION_TYPE);
			MAIN_SETTINGS_BLOCK.AddChild(&NORMAL_VECTOR);
			NORMAL_VECTOR.SetDisplayPredicate(ValueEqualsPredicate<EnumLikeValue*>::Of(&EFFECT_ROTATION_TYPE, &EnumLikeValue::FIXED));

			MAIN_SETTINGS_BLOCK.AddChild(&TRAIL_SETTINGS_BLOCK);
			{
				TRAIL_SETTINGS_BLOCK.AddChild(&SMOKE_TRAIL_SETTINGS_BLOCK);
				{
					SMOKE_TRAIL_SETTINGS_BLOCK.AddChild(&USE_SMOKE_TRAIL);
					SMOKE_TRAIL_SETTINGS_BLOCK.AddChild(&SMOKE_TRAIL_LIFETIME);
					SMOKE_TRAIL_SETTINGS_BLOCK.AddChild(&SMOKE_TRAIL_SPREAD);
					SMOKE_TRAIL_SETTINGS_BLOCK.AddChild(&SMOKE_TRAIL_EMISSION_DURATION);
					SMOKE_TRAIL_SETTINGS_BLOCK.AddChild(&SMOKE_TRAIL_SPRITE_SIZE);
					SMOKE_TRAIL_SETTINGS_BLOCK.AddChild(&SMOKE_TRAIL_INTENSITY);
				}

				TRAIL_SETTINGS_BLOCK.AddChild(&WILLOW_TRAIL_SETTINGS_BLOCK);
				{
					WILLOW_TRAIL_SETTINGS_BLOCK.AddChild(&USE_WILLOW_TRAIL);
					WILLOW_TRAIL_SETTINGS_BLOCK.AddChild(&WILLOW_TRAIL_SPREAD);
					WILLOW_TRAIL_SETTINGS_BLOCK.AddChild(&WILLOW_TRAIL_SPAWN_RATE);
					WILLOW_TRAIL_SETTINGS_BLOCK.AddChild(&WILLOW_TRAIL_SPRITE_SIZE);
					WILLOW_TRAIL_SETTINGS_BLOCK.AddChild(&WILLOW_TRAIL_EMISSION_DURATION);
					WILLOW_TRAIL_SETTINGS_BLOCK.AddChild(WILLOW_TRAIL_LIFETIME.GetBlockParam());
					WILLOW_TRAIL_SETTINGS_BLOCK.AddChild(&WILLOW_TRAIL_EJECTION_SPEED);
				}

				TRAIL_SETTINGS_BLOCK.AddChild(&CRACKLE_TRAIL_SETTINGS_BLOCK);
				{
					CRACKLE_TRAIL_SETTINGS_BLOCK.AddChild(&USE_CRACKLE_TRAIL);
					CRACKLE_TRAIL_SETTINGS_BLOCK.AddChild(&CRACKLE_TRAIL_SPREAD);
					CRACKLE_TRAIL_SETTINGS_BLOCK.AddChild(&CRACKLE_TRAIL_SPAWN_RATE);
					CRACKLE_TRAIL_SETTINGS_BLOCK.AddChild(&CRACKLE_TRAIL_SPRITE_SIZE);
					CRACKLE_TRAIL_SETTINGS_BLOCK.AddChild(&CRACKLE_TRAIL_EMISSION_DURATION);
					CRACKLE_TRAIL_SETTINGS_BLOCK.AddChild(CRACKLE_TRAIL_LIFETIME.GetBlockParam());
					CRACKLE_TRAIL_SETTINGS_BLOCK.AddChild(&CRACKLE_TRAIL_EJECTION_SPEED);
				}
			}
			MAIN_SETTINGS_BLOCK.AddChild(&COLOR_EFFECT_SETTINGS);
			{
				COLOR_EFFECT_SETTINGS.AddChild(&COLOR_EFFECT_TYPE);

				COLOR_EFFECT_SETTINGS.AddChild(&SIMPLE_COLOR_CHANGE_BLOCK);
				{
					SIMPLE_COLOR_CHANGE_BLOCK.SetDisplayPredicate(
						ValueEqualsPredicate<EnumLikeValue*>::Of(&COLOR_EFFECT_TYPE, &EnumLikeValue::SIMPLE_COLOR_CHANGE));
					SIMPLE_COLOR_CHANGE_BLOCK.AddChild(&LERP_START_TIME);
					SIMPLE_COLOR_CHANGE_BLOCK.AddChild(&LERP_END_TIME);
					SIMPLE_COLOR_CHANGE_BLOCK.AddChild(&TARGET_COLOR);
				}

				COLOR_EFFECT_SETTINGS.AddChild(&COLOR_FLARE_BLOCK);
				{
					COLOR_FLARE_BLOCK.SetDisplayPredicate(ValueEqualsPredicate<EnumLikeValue*>::Of(&COLOR_EFFECT_TYPE, &EnumLikeValue::FLARE));
					COLOR_FLARE_BLOCK.AddChild(&LERP_START_TIME);
					COLOR_FLARE_BLOCK.AddChild(&LERP_END_TIME);
					COLOR_FLARE_BLOCK.AddChild(&TARGET_COLOR);
				}

				COLOR_EFFECT_SETTINGS.AddChild(&COLOR_FLICKER_BLOCK);
				{
					COLOR_FLICKER_BLOCK.SetDisplayPredicate(ValueEqualsPredicate<EnumLikeValue*>::Of(&COLOR_EFFECT_TYPE, &EnumLikeValue::FLICKER));
					COLOR_FLICKER_BLOCK.AddChild(&LERP_START_TIME);
					COLOR_FLICKER_BLOCK.AddChild(&LERP_END_TIME);
					COLOR_FLICKER_BLOCK.AddChild(&TARGET_COLOR);
				}

				COLOR_EFFECT_SETTINGS.AddChild(&COLOR_WAVE_BLOCK);
				{
					COLOR_WAVE_BLOCK.SetDisplayPredicate(ValueEqualsPredicate<EnumLikeValue*>::Of(&COLOR_EFFECT_TYPE, &EnumLikeValue::COLOR_WAVE));
					COLOR_WAVE_BLOCK.AddChild(&LERP_START_TIME);
					COLOR_WAVE_BLOCK.AddChild(&LERP_END_TIME);
					COLOR_WAVE_BLOCK.AddChild(&TARGET_COLOR);
					COLOR_WAVE_BLOCK.AddChild(&WAVE_CYCLE_PERCENT);
				}

				COLOR_EFFECT_SETTINGS.AddChild(&ADVANCE_COLOR_LERP_BLOCK);
				{
					ADVANCE_COLOR_LERP_BLOCK.SetDisplayPredicate(
						ValueEqualsPredicate<EnumLikeValue*>::Of(&COLOR_EFFECT_TYPE, &EnumLikeValue::ADVANCED_COLOR_LERP));
					ADVANCE_COLOR_LERP_BLOCK.AddChild(&TARGET_COLOR);
					ADVANCE_COLOR_LERP_BLOCK.AddChild(&LERP_START_TIME);
					ADVANCE_COLOR_LERP_BLOCK.AddChild(&LERP_END_TIME);
					ADVANCE_COLOR_LERP_BLOCK.AddChild(&LERP_FREQUENCY);
					ADVANCE_COLOR_LERP_BLOCK.AddChild(&LERP_PHASE_COUNT);
					ADVANCE_COLOR_LERP_BLOCK.AddChild(&LERP_WAVE_DUTY_CYCLE);
				}
			}
		}

		/**
		 * Compound effect setup
		 */
		MAIN_SETTINGS_BLOCK.AddChild(&SOS_CONFIGS_LIST);

		SOS_CONFIG_BLOCK.AddChild(&SOS_CHILD_SHELLS_NUM);
		SOS_CONFIG_BLOCK.AddChild(SOS_EFFECT_TIME.GetBlockParam());
		SOS_CONFIG_BLOCK.AddChild(&SOS_EFFECT_SHAPE);
		SOS_CONFIG_BLOCK.AddChild(&SOS_DELAY_TYPE);
		SOS_DELAY_TYPE.SetDisplayPredicate(ValueEqualsPredicate<EnumLikeValue*>::Of(&SOS_EFFECT_SHAPE, &EnumLikeValue::SOS_FROM_PARENT_PARTICLES));
		SOS_CONFIG_BLOCK.AddChild(&SOS_RECURRING_MAX_NUM);
		SOS_RECURRING_MAX_NUM.SetDisplayPredicate(ValueEqualsPredicate<EnumLikeValue*>::Of(&SOS_DELAY_TYPE, &EnumLikeValue::SOS_DELAY_AT_REGULAR_INTERVAL));

		SOS_CONFIG_BLOCK.AddChild(&SOS_SPHERE_BLOCK);
		SOS_SPHERE_BLOCK.SetDisplayPredicate(ValueEqualsPredicate<EnumLikeValue*>::Of(&SOS_EFFECT_SHAPE, &EnumLikeValue::SOS_SPHERE));
		SOS_SPHERE_BLOCK.AddChild(SOS_SHAPE_SCALE.GetBlockParam());


		SOS_CONFIG_BLOCK.AddChild(&SOS_RING_BLOCK);
		SOS_RING_BLOCK.SetDisplayPredicate(ValueEqualsPredicate<EnumLikeValue*>::Of(&SOS_EFFECT_SHAPE, &EnumLikeValue::SOS_RING));
		SOS_RING_BLOCK.AddChild(SOS_SHAPE_SCALE.GetBlockParam());
		SOS_RING_BLOCK.AddChild(&SOS_SHAPE_NORMAL);

		SOS_CONFIG_BLOCK.AddChild(&SOS_EFFECT_PICKER);


		DEFAULT_SYSTEM = LoadObject<UNiagaraSystem>(GetTransientPackage(), TEXT("/Game/FireVRks/Effects/Systems/FibonacciSphere.FibonacciSphere"));

		//TECHNICAL PARAMETERS
		MAIN_SETTINGS_BLOCK.AddChild(&USE_DISTANCE_CORRECTION);
		MAIN_SETTINGS_BLOCK.AddChild(&DISTANCE_CORRECTION_SETTINGS);
		DISTANCE_CORRECTION_SETTINGS.SetDisplayPredicate(ValueEqualsPredicate<bool>::Of(&USE_DISTANCE_CORRECTION, true));
		DISTANCE_CORRECTION_SETTINGS.AddChild(&DISTANCE_CORRECTION_SCALE);
		DISTANCE_CORRECTION_SETTINGS.AddChild(&DISTANCE_CORRECTION_EXPONENT);

		MAIN_SETTINGS_BLOCK.AddChild(&DRAG_SETTINGS);
		DRAG_SETTINGS.AddChild(&DRAG_EXPONENT);
		DRAG_SETTINGS.AddChild(&DRAG_LOW_SPEED_SCALE);
		DRAG_SETTINGS.AddChild(&DRAG_HIGH_SPEED_SCALE);

		IsInit = true;
	}
}

void UDefaultParameterSystem::AddParameter(AbstractFormalParameter* Parameter)
{
	Parameters.Add(Parameter);
}

TArray<AbstractFormalParameter*> UDefaultParameterSystem::GetOuterParameters()
{
	return Parameters;
}

FString UDefaultParameterSystem::GetId()
{
	return "_Internal_.DEFAULT_EFFECT";
}

FString UDefaultParameterSystem::GetName()
{
	return "Default System";
}

UTexture2D* UDefaultParameterSystem::GetIcon()
{
	return DFStyleUtil::LoadCachedTexture("DefaultEffectIcon", "/Game/FireVRks/UI/Icons/DefaultEffectIcon.DefaultEffectIcon");
}


void UDefaultParameterSystem::SpawnSystem(EffectSpawnData* Data, AActor* PlayerRef)
{
	auto Context = Data->GetContext();

	auto Location = Data->GetSpawnTarget()->GetActorLocation() + Data->GetOffset();

	auto Distance = 20000;
	if (PlayerRef)
	{
		Location.Distance(Location, PlayerRef->GetActorLocation());
	}

	auto Effect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(Data->GetSpawnTarget(), DEFAULT_SYSTEM, Location);

	auto RotationType = EFFECT_ROTATION_TYPE.GetValue(Context);

	FVector Normal;
	switch (RotationType->GetOrdinal())
	{
		default:
		case 0: Normal = FVector(NORMAL_VECTOR.GetValue(Context));
			break;
		case 1:
			{
				Normal = Data->GetUpwards();
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
	Effect->SetNiagaraVariableInt("SpriteSizeMin", SPRITE_SIZE.GetMin(Context));
	Effect->SetNiagaraVariableInt("SpriteSizeMax", SPRITE_SIZE.GetMax(Context));

	Effect->SetNiagaraVariableFloat("StarsLifetimeMin", LIFETIME.GetMin(Context));
	Effect->SetNiagaraVariableFloat("StarsLifetimeMax", LIFETIME.GetMax(Context));

	Effect->SetNiagaraVariableInt("InitialVelocityMin", VELOCITY.GetMin(Context));
	Effect->SetNiagaraVariableInt("InitialVelocityMax", VELOCITY.GetMax(Context));

	Effect->SetColorParameter("Color1", MAIN_COLOR.GetValue(Context));
	Effect->SetColorParameter("Color2", USE_SECOND_COLOR.GetValue(Context) ? SECONDARY_COLOR.GetValue(Context) : MAIN_COLOR.GetValue(Context));

	Effect->SetIntParameter("StarsCount", SPRITE_COUNT.GetValue(Context));


	//TRAILS
	Effect->SetBoolParameter("EnableSmokeTrails", USE_SMOKE_TRAIL.GetValue(Context));
	Effect->SetFloatParameter("SmokeTrailSpread", SMOKE_TRAIL_SPREAD.GetValue(Context));
	Effect->SetFloatParameter("SmokeTrailLifetime", SMOKE_TRAIL_LIFETIME.GetValue(Context));
	Effect->SetFloatParameter("SmokeTrailIntensity", SMOKE_TRAIL_INTENSITY.GetValue(Context));
	Effect->SetFloatParameter("SmokeTrailSpriteSize", SMOKE_TRAIL_SPRITE_SIZE.GetValue(Context));
	Effect->SetFloatParameter("SmokeTrailEmissionDuration", SMOKE_TRAIL_EMISSION_DURATION.GetValue(Context));

	Effect->SetBoolParameter("EnableCrackleTrails", USE_CRACKLE_TRAIL.GetValue(Context));
	Effect->SetFloatParameter("CrackleTrailSpread", CRACKLE_TRAIL_SPREAD.GetValue(Context));
	Effect->SetFloatParameter("CrackleTrailEjectionSpeed", CRACKLE_TRAIL_EJECTION_SPEED.GetValue(Context));
	Effect->SetFloatParameter("CrackleTrailMaxLifetime", CRACKLE_TRAIL_LIFETIME.GetMax(Context));
	Effect->SetFloatParameter("CrackleTrailMinLifetime", CRACKLE_TRAIL_LIFETIME.GetMin(Context));
	Effect->SetFloatParameter("CrackleTrailSpriteSize", CRACKLE_TRAIL_SPRITE_SIZE.GetValue(Context));
	Effect->SetFloatParameter("CrackleTrailSpawnRate", CRACKLE_TRAIL_SPAWN_RATE.GetValue(Context));
	Effect->SetFloatParameter("CrackleTrailEmissionDuration", CRACKLE_TRAIL_EMISSION_DURATION.GetValue(Context));


	Effect->SetBoolParameter("EnableWillowTrails", USE_WILLOW_TRAIL.GetValue(Context));
	Effect->SetFloatParameter("WillowTrailSpread", WILLOW_TRAIL_SPREAD.GetValue(Context));
	Effect->SetFloatParameter("WillowTrailEjectionSpeed", WILLOW_TRAIL_EJECTION_SPEED.GetValue(Context));
	Effect->SetFloatParameter("WillowTrailMaxLifetime", WILLOW_TRAIL_LIFETIME.GetMax(Context));
	Effect->SetFloatParameter("WillowTrailMinLifetime", WILLOW_TRAIL_LIFETIME.GetMin(Context));
	Effect->SetFloatParameter("WillowTrailSpriteSize", WILLOW_TRAIL_SPRITE_SIZE.GetValue(Context));
	Effect->SetFloatParameter("WillowTrailSpawnRate", WILLOW_TRAIL_SPAWN_RATE.GetValue(Context));
	Effect->SetFloatParameter("WillowTrailEmissionDuration", WILLOW_TRAIL_EMISSION_DURATION.GetValue(Context));
	//--------


	Effect->SetFloatParameter("SimpleColorLerpStart", LERP_START_TIME.GetValue(Context));
	Effect->SetFloatParameter("SimpleColorLerpEnd", LERP_END_TIME.GetValue(Context));
	Effect->SetColorParameter("Color3", TARGET_COLOR.GetValue(Context));
	if (COLOR_EFFECT_TYPE.GetValue(Context) == &EnumLikeValue::NO_EFFECT)
	{
		Effect->SetBoolParameter("UseSimpleColorLerp", false);
	}
	else if (COLOR_EFFECT_TYPE.GetValue(Context) == &EnumLikeValue::SIMPLE_COLOR_CHANGE)
	{
		Effect->SetBoolParameter("UseSimpleColorLerp", true);
		Effect->SetFloatParameter("SimpleLerpFrequency", 1.0f);
		Effect->SetIntParameter("ColorLerpPhaseCount", 1);
		Effect->SetFloatParameter("PhaseOverlapFraction", 0.0f);
	}
	else if (COLOR_EFFECT_TYPE.GetValue(Context) == &EnumLikeValue::FLARE)
	{
		Effect->SetBoolParameter("UseSimpleColorLerp", true);
		Effect->SetFloatParameter("SimpleLerpFrequency", 2.0f);
		Effect->SetIntParameter("ColorLerpPhaseCount", COLOR_FLARE_GROUP_COUNT.GetValue(Context));
		Effect->SetFloatParameter("PhaseOverlapFraction", 0.0f);
	}
	else if (COLOR_EFFECT_TYPE.GetValue(Context) == &EnumLikeValue::FLICKER)
	{
		Effect->SetBoolParameter("UseSimpleColorLerp", true);
		Effect->SetFloatParameter("SimpleLerpFrequency", 2.0f);
		Effect->SetIntParameter("ColorLerpPhaseCount", SPRITE_COUNT.GetValue(Context));
		Effect->SetBoolParameter("RandomizeParticleOrder", true);
		Effect->SetFloatParameter("PhaseOverlapFraction", 0.8f);
	}
	else if (COLOR_EFFECT_TYPE.GetValue(Context) == &EnumLikeValue::COLOR_WAVE)
	{
		Effect->SetBoolParameter("UseSimpleColorLerp", true);
		Effect->SetFloatParameter("SimpleLerpFrequency", 2.0f);
		Effect->SetIntParameter("ColorLerpPhaseCount", SPRITE_COUNT.GetValue(Context));
		Effect->SetBoolParameter("RandomizeParticleOrder", false);
		Effect->SetFloatParameter("PhaseOverlapFraction", 0.9f + WAVE_CYCLE_PERCENT.GetValue(Context) / 1000.f);
	}
	else if (COLOR_EFFECT_TYPE.GetValue(Context) == &EnumLikeValue::ADVANCED_COLOR_LERP)
	{
		Effect->SetBoolParameter("UseSimpleColorLerp", true);
		Effect->SetFloatParameter("SimpleLerpFrequency", LERP_FREQUENCY.GetValue(Context));
		Effect->SetIntParameter("ColorLerpPhaseCount", LERP_PHASE_COUNT.GetValue(Context));
		Effect->SetFloatParameter("PhaseOverlapFraction", LERP_WAVE_DUTY_CYCLE.GetValue(Context));
	}
	Effect->SetIntParameter("ShapeType", EFFECT_SHAPE.GetValue(Context)->GetOrdinal());

	Effect->SetIntParameter("ClusterSize", CLUSTER_SIZE.GetValue(Context));
	Effect->SetFloatParameter("ClusterSpacing", CLUSTER_SPACING.GetValue(Context));
	Effect->SetIntParameter("ConeAngle", CONE_ANGLE.GetValue(Context));
	Effect->SetIntParameter("ConeAngleVariance", CONE_ANGLE_VARIANCE.GetValue(Context));
	Effect->SetBoolParameter("ConeSurfaceOnly", CONE_SURFACE_ONLY.GetValue(Context));
	Effect->SetBoolParameter("ConeUniform", CONE_UNIFORM.GetValue(Context));
	Effect->SetBoolParameter("ConeBiDirectional", CONE_BI_DIRECTIONAL.GetValue(Context));


	//TECHNICAL SETTINGS
	Effect->SetBoolParameter("UseDistanceCorrection", USE_DISTANCE_CORRECTION.GetValue(Context));
	Effect->SetFloatParameter("DistanceCorrectionExponent", DISTANCE_CORRECTION_EXPONENT.GetValue(Context));
	Effect->SetFloatParameter("DistanceCorrectionLinearScale", DISTANCE_CORRECTION_SCALE.GetValue(Context));
	Effect->SetFloatParameter("Distance", 20000);

	Effect->SetFloatParameter("DragExponent", DRAG_EXPONENT.GetValue(Context));
	Effect->SetFloatParameter("LowSpeedDragScale", DRAG_LOW_SPEED_SCALE.GetValue(Context));
	Effect->SetFloatParameter("HighSpeedDragScale", DRAG_HIGH_SPEED_SCALE.GetValue(Context));
	Effect->SetFloatParameter("Distance", Distance);


	//SOS Spawning
	//SOS-subsystem contexts are stored in the list parameter value; Inside each, the SystemInstantiationParameter stores the actual sub-instance-context
	auto SosBlocks = Context->GetValue<ListParameterValue>(&SOS_CONFIGS_LIST)->GetValues();
	if (!SosBlocks.IsEmpty())
	{
		ACallbackSystemDriver* Handler = nullptr;

		for (ParameterValueContext* SOSContext : SosBlocks)
		{
			auto StartTime = SOS_EFFECT_TIME.GetMin(SOSContext);
			auto EndTime = SOS_EFFECT_TIME.GetMax(SOSContext);
			auto ChildEffectsNum = SOS_CHILD_SHELLS_NUM.GetValue(SOSContext);


			auto World = GEngine->GetWorldFromContextObject(Effect, EGetWorldErrorMode::ReturnNull);

			auto SosShape = SOS_EFFECT_SHAPE.GetValue(SOSContext);

			auto SystemInstanceParams = SOSContext->GetValue<SystemInstantiationParameterValue>(&SOS_EFFECT_PICKER);

			if (SosShape == &EnumLikeValue::SOS_FROM_PARENT_PARTICLES)
			{
				if (Handler == nullptr)
				{
					Handler = World->SpawnActor<ACallbackSystemDriver>(FVector(Location), FRotator());
					Handler->SetActorTickEnabled(true);
					Handler->Init(SPRITE_COUNT.GetValue(Context), LIFETIME.GetMax(Context), Effect);
				}

				auto SpawnData = new EffectSpawnData(
					SystemInstanceParams->GetSystem(),
					SystemInstanceParams->GetContext(),
					Data->GetSpawnTarget(),
					0,
					FVector(),
					Normal
				);
				Handler->AddSpawnInfo(
					SpawnData,
					SOS_EFFECT_TIME.GetMin(SOSContext),
					SOS_EFFECT_TIME.GetMax(SOSContext),
					SOS_CHILD_SHELLS_NUM.GetValue(SOSContext),
					SOS_DELAY_TYPE.GetValue(SOSContext),
					SOS_RECURRING_MAX_NUM.GetValue(SOSContext)
				);
			}
			else
			{
				for (int i = 0; i < ChildEffectsNum; i++)
				{
					auto SpawnDelay = FMath::RandRange(StartTime, EndTime);


					int Scale = FMath::RandRange(SOS_SHAPE_SCALE.GetMin(SOSContext), SOS_SHAPE_SCALE.GetMax(SOSContext));
					FVector Offset;

					switch (SosShape->GetOrdinal())
					{
						case 1: Offset = FMath::VRand() * Scale;
							break;
						case 2:
							{
								auto Quat = UKismetMathLibrary::Quat_FindBetweenVectors(
									FVector(0, 1, 0), FVector(SOS_SHAPE_NORMAL.GetValue(SOSContext))
								);
								float Phase = (M_PI * 2 * i) / ChildEffectsNum;
								FVector Rad = (FVector(1, 0, 0) * FMath::Sin(Phase) + FVector(0, 0, 1) * FMath::Cos(Phase));
								Offset = Quat.RotateVector(Rad) * Scale;
							}

						default: break;
					}

					UEffectSystemScheduler::INSTANCE->ScheduleSpawn(
						new EffectSpawnData(
							SystemInstanceParams->GetSystem(), SystemInstanceParams->GetContext(), Data->GetSpawnTarget(), SpawnDelay, Offset)
					);
				}
			}
		}
		if (Handler != nullptr)
		{
			Handler->Finalize();
		}
	}
}
