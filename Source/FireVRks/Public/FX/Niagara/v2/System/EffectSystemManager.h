#pragma once
#include "CustomEffectSystem.h"
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

	UPROPERTY()
	UCustomEffectSystem* SystemInEditing;

public:
	
	void Initialize();

	void Register(UEffectSystem* System);

	UDefaultParameterSystem* GetDefaultEffect() const;

	static UEffectSystemManager* Instance();

	UEffectSystem* Get(UDFId* Id);

	void List(TArray<UEffectSystem*>& Systems);

	UCustomEffectSystem* GetSystemInEditing() const;
};
