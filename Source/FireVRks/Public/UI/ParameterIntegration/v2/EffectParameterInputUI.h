#pragma once
#include "ParameterInputUI.h"
#include "FX/Niagara/v2/System/EffectSystem.h"
#include "EffectParameterInputUI.generated.h"

UCLASS(Blueprintable, BlueprintType)
class FIREVRKS_API UEffectParameterInputUI : public UParameterInputUI
{
	GENERATED_BODY()

	UPROPERTY()
	UEffectSystem* System = nullptr;
	
public:
	UEffectParameterInputUI();

	void SetSystem(UEffectSystem* FSystem)
	{
		this->System = FSystem;
		this->SetProvider(FSystem);
	}
};

