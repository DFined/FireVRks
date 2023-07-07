#include "EffectSystemManager.h"


TMap<FString, UEffectSystem*> EffectSystemManager::Effects = TMap<FString, UEffectSystem*>();
UDefaultParameterSystem* EffectSystemManager::DEFAULT_EFFECT = UDefaultParameterSystem::Make();

void EffectSystemManager::Initialize()
{
	Register(DEFAULT_EFFECT);
}

void EffectSystemManager::Register(UEffectSystem* System)
{
	System->Initialize();
	Effects.Add(System->GetId(), System);
}
