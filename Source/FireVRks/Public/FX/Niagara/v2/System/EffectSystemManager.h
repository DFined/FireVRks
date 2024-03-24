#pragma once
#include "CustomEffectSystem.h"
#include "EffectSystem.h"
#include "EffectSystemManager.generated.h"

class UGroundEffectParameterSystem;
class UDefaultParameterSystem;

UCLASS()
class FIREVRKS_API UEffectSystemManager : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<FDFId, UEffectSystem*> Effects;

	UPROPERTY()
	UDefaultParameterSystem* DEFAULT_EFFECT;

	UPROPERTY()
	UGroundEffectParameterSystem* GROUND_EFFECT;

	UPROPERTY()
	UCustomEffectSystem* SystemInEditing;

public:
	void Init();

	void Register(UEffectSystem* System);

	UDefaultParameterSystem* GetDefaultEffect() const;

	static UEffectSystemManager* Instance();

	UEffectSystem* Get(FDFId Id);

	void List(TArray<UEffectSystem*>& Systems);

	UCustomEffectSystem* GetSystemInEditing() const;
	void LoadSystem(FString Path);

	void TraverseAndLoadSystems();

	void SaveEffect(UCustomEffectSystem* System);

	void SetSystemInEditing(UCustomEffectSystem* SystemInEditing);

	UFUNCTION(BlueprintCallable)
	static UEffectSystemManager* GetInstance()
	{
		if (!SingleInstance.IsValid())
		{
			SingleInstance = NewObject<UEffectSystemManager>();
			SingleInstance->AddToRoot();
			SingleInstance->Init();
		}
		return SingleInstance.Get();
	}

private:
	inline static TWeakObjectPtr<UEffectSystemManager> SingleInstance = nullptr;
};
