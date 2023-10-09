#include "FX/Niagara/v2/System/EffectSystemManager.h"

#include "FX/Niagara/v2/System/DefaultParameterSystem.h"
#include "FX/Niagara/v2/System/EffectSystem.h"


void UEffectSystemManager::Initialize()
{
	Effects = TMap<UDFId*, UEffectSystem*>();
	Effects.Empty();
	DEFAULT_EFFECT = UDefaultParameterSystem::Make();
	Register(DEFAULT_EFFECT);
}

void UEffectSystemManager::Register(UEffectSystem* System)
{
	Effects.Add(System->GetId(), System);
}

UDefaultParameterSystem* UEffectSystemManager::GetDefaultEffect() const
{
	return DEFAULT_EFFECT;
}

UEffectSystemManager* UEffectSystemManager::Instance()
{
	auto Manager = UDFStatics::New<UEffectSystemManager>();
	Manager->Initialize();
	return Manager;
}

UEffectSystem* UEffectSystemManager::Get(UDFId* Id)
{
	if(auto Res = Effects.Find(Id))
	{
		return *Res;
	}
	return nullptr;
}
