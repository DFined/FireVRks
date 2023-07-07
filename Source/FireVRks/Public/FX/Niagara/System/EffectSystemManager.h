#pragma once
#include "DefaultParameterSystem.h"
#include "EffectSystem.h"

class EffectSystemManager
{
	static TMap<FString, UEffectSystem*> Effects;

public:
	static UDefaultParameterSystem* DEFAULT_EFFECT;
	
	static void Initialize();

	static void Register(UEffectSystem* System);


	static void Search(FString Id)
	{
		
	}  
	
};
