#include "FX/Niagara/SystemSettings/ParamSystem/DefaultParameterSystem.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "FX/Niagara/SystemSettings/FormalParameter/ValueEqualsPredicate.h"

TArray<AbstractFormalParameter*> UDefaultParameterSystem::Parameters = TArray<AbstractFormalParameter*>();
bool UDefaultParameterSystem::IsInit = false;

BlockCompoundParameter UDefaultParameterSystem::MAIN_SETTINGS_BLOCK = BlockCompoundParameter(
	"Effect Settings", true, true, true
);

EnumFormalParameter UDefaultParameterSystem::EFFECT_SHAPE = EnumFormalParameter(
	"Effect shape", true, &EnumLike::BURST_SHAPE, true
);

BlockCompoundParameter UDefaultParameterSystem::PEONY_SETTINGS_BLOCK = BlockCompoundParameter(
	"Peony options", true, true, true
);


CompoundableFormalParameter<int> UDefaultParameterSystem::VELOCITY = CompoundableFormalParameter(
	 "Velocity", DFType::TYPED_INT_PARAMETER, true, 5000
);

CompoundableFormalParameter<float> UDefaultParameterSystem::LIFETIME = CompoundableFormalParameter(
	"Sprite Lifetime", DFType::TYPED_FLOAT_PARAMETER, true, 2.0f
);

CompoundableFormalParameter<int> UDefaultParameterSystem::SPRITE_SIZE = CompoundableFormalParameter(
	"Sprite size", DFType::TYPED_INT_PARAMETER, true, 50);

FormalParameter<FLinearColor> UDefaultParameterSystem::MAIN_COLOR = FormalParameter(
	DFType::TYPED_VECTOR_PARAMETER, "Main color", true, FLinearColor(255, 0, 0), true
);

FormalParameter<int> UDefaultParameterSystem::SPRITE_COUNT = FormalParameter(
	DFType::TYPED_INT_PARAMETER, "Star count", true, 50, true
);


FormalParameter<bool> UDefaultParameterSystem::USE_DISTANCE_CORRECTION = FormalParameter(
	DFType::TYPED_BOOL_PARAMETER, "Use distance correction", false, true, true
);

FormalParameter<float> UDefaultParameterSystem::DISTANCE_CORRECTION_SCALE = FormalParameter(
	DFType::TYPED_FLOAT_PARAMETER, "Distance correction scale", false, 1.0f, true
);

/**Trail settings*/
BlockCompoundParameter UDefaultParameterSystem::TRAIL_SETTINGS_BLOCK = BlockCompoundParameter(
	"Trails", true, true, true
);

BlockCompoundParameter UDefaultParameterSystem::SMOKE_TRAIL_SETTINGS_BLOCK = BlockCompoundParameter(
	"Smoke trail settings", true, true, true
);
FormalParameter<bool> UDefaultParameterSystem::USE_SMOKE_TRAIL = FormalParameter(DFType::TYPED_BOOL_PARAMETER, "Use smoke trail", true, false, true);


BlockCompoundParameter UDefaultParameterSystem::CRACKLE_TRAIL_SETTINGS_BLOCK = BlockCompoundParameter(
	"Crackle trail settings", true, true, true
);
FormalParameter<bool> UDefaultParameterSystem::USE_CRACKLE_TRAIL = FormalParameter(DFType::TYPED_BOOL_PARAMETER, "Use crackle trail", true, false, true);


BlockCompoundParameter UDefaultParameterSystem::WILLOW_TRAIL_SETTINGS_BLOCK= BlockCompoundParameter(
	"Spark trail settings", true, true, true
);
FormalParameter<bool> UDefaultParameterSystem::USE_WILLOW_TRAIL = FormalParameter(DFType::TYPED_BOOL_PARAMETER, "Use willow trail", true, false, true);


BlockCompoundParameter UDefaultParameterSystem::COLOR_EFFECT_SETTINGS = BlockCompoundParameter("Color effects", true, true, false);
BlockCompoundParameter UDefaultParameterSystem::LERP_COLOR_BLOCK = BlockCompoundParameter("Color lerp", true, true, false);
FormalParameter<bool> UDefaultParameterSystem::USE_COLOR_LERP = FormalParameter(
	DFType::TYPED_BOOL_PARAMETER, "Lerp color", true, false, true
	);
FormalParameter<FLinearColor> UDefaultParameterSystem::SECONDARY_COLOR = FormalParameter(
	DFType::TYPED_VECTOR_PARAMETER, "Secondary color", true, FLinearColor(255,255,255), true
	);

UNiagaraSystem* UDefaultParameterSystem::DEFAULT_SYSTEM = nullptr;

void UDefaultParameterSystem::Initialize()
{
	if (!IsInit)
	{
		AddParameter(&MAIN_SETTINGS_BLOCK);
		{
			MAIN_SETTINGS_BLOCK.AddChild(&EFFECT_SHAPE);
			MAIN_SETTINGS_BLOCK.AddChild(&PEONY_SETTINGS_BLOCK);
			{
				PEONY_SETTINGS_BLOCK.SetDisplayPredicate(ValueEqualsPredicate<EnumLikeValue*>::Of(&EFFECT_SHAPE, &EnumLikeValue::PEONY));
			}
			MAIN_SETTINGS_BLOCK.AddChild(&SPRITE_COUNT);
			PEONY_SETTINGS_BLOCK.AddChild(VELOCITY.GetBlockParam());
			MAIN_SETTINGS_BLOCK.AddChild(&MAIN_COLOR);
			MAIN_SETTINGS_BLOCK.AddChild(LIFETIME.GetBlockParam());
			MAIN_SETTINGS_BLOCK.AddChild(SPRITE_SIZE.GetBlockParam());
			MAIN_SETTINGS_BLOCK.AddChild(&USE_DISTANCE_CORRECTION);
			MAIN_SETTINGS_BLOCK.AddChild(&DISTANCE_CORRECTION_SCALE);
			DISTANCE_CORRECTION_SCALE.SetDisplayPredicate(ValueEqualsPredicate<bool>::Of(&USE_DISTANCE_CORRECTION, true));
			MAIN_SETTINGS_BLOCK.AddChild(&TRAIL_SETTINGS_BLOCK);
			{
				TRAIL_SETTINGS_BLOCK.AddChild(&SMOKE_TRAIL_SETTINGS_BLOCK);
				{
					SMOKE_TRAIL_SETTINGS_BLOCK.AddChild(&USE_SMOKE_TRAIL);
				}
			
				TRAIL_SETTINGS_BLOCK.AddChild(&WILLOW_TRAIL_SETTINGS_BLOCK);
				{
					WILLOW_TRAIL_SETTINGS_BLOCK.AddChild(&USE_WILLOW_TRAIL);
				}
				
				TRAIL_SETTINGS_BLOCK.AddChild(&CRACKLE_TRAIL_SETTINGS_BLOCK);
				{
					CRACKLE_TRAIL_SETTINGS_BLOCK.AddChild(&USE_CRACKLE_TRAIL);
				}
			
			}
			MAIN_SETTINGS_BLOCK.AddChild(&COLOR_EFFECT_SETTINGS);
			{
				COLOR_EFFECT_SETTINGS.AddChild(&SECONDARY_COLOR);
				COLOR_EFFECT_SETTINGS.AddChild(&USE_COLOR_LERP);
				COLOR_EFFECT_SETTINGS.AddChild(&LERP_COLOR_BLOCK);
				LERP_COLOR_BLOCK.SetDisplayPredicate(ValueEqualsPredicate<bool>::Of(&USE_COLOR_LERP, true));
			}
		}
		DEFAULT_SYSTEM = LoadObject<UNiagaraSystem>(GetTransientPackage(), TEXT("/Game/FireVRks/Effects/Systems/FibonacciSphere.FibonacciSphere"));
		IsInit = true;
	}
}

void UDefaultParameterSystem::AddParameter(AbstractFormalParameter* Parameter)
{
	Parameters.Add(Parameter);
}


void UDefaultParameterSystem::SpawnSystem(AActor* Target)
{
	auto Effect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(Target, DEFAULT_SYSTEM, Target->GetActorLocation());

	//Actually transfer all the settings to the system
	Effect->SetNiagaraVariableInt("SpriteSizeMin", SPRITE_SIZE.GetMin(Context));
	Effect->SetNiagaraVariableInt("SpriteSizeMax", SPRITE_SIZE.GetMax(Context));

	Effect->SetNiagaraVariableFloat("StarsLifetimeMin", LIFETIME.GetMin(Context));
	Effect->SetNiagaraVariableFloat("StarsLifetimeMax", LIFETIME.GetMax(Context));
	
	Effect->SetNiagaraVariableInt("InitialVelocityMin", VELOCITY.GetMin(Context));
	Effect->SetNiagaraVariableInt("InitialVelocityMax", VELOCITY.GetMax(Context));

	Effect->SetColorParameter("Color1", MAIN_COLOR.GetValue(Context));

	Effect->SetIntParameter("StarsCount", SPRITE_COUNT.GetValue(Context));

	Effect->SetBoolParameter("EnableCrackleTrails", USE_CRACKLE_TRAIL.GetValue(Context));
	Effect->SetBoolParameter("EnableSmokeTrails", USE_SMOKE_TRAIL.GetValue(Context));
	Effect->SetBoolParameter("EnableWillowTrails", USE_WILLOW_TRAIL.GetValue(Context));

	Effect->SetBoolParameter("EnableColorLerp", USE_COLOR_LERP.GetValue(Context));
	Effect->SetColorParameter("Color2", SECONDARY_COLOR.GetValue(Context));
}
