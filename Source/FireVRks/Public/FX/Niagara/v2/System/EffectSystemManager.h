#pragma once
#include "EffectSystem.h"
#include "EffectSystemManager.generated.h"

class UDefaultParameterSystem;

UCLASS()
class FIREVRKS_API UEffectSystemManager : public UObject
{
	GENERATED_BODY()
	
	UPROPERTY()
	TMap<UDFId*, UEffectSystem*> Effects;
	
	UPROPERTY()
	UDefaultParameterSystem* DEFAULT_EFFECT;

public:
	
	void Initialize();

	void Register(UEffectSystem* System);

	UDefaultParameterSystem* GetDefaultEffect() const;

	static UEffectSystemManager* Instance();

	UEffectSystem* Get(UDFId* Id);
};
