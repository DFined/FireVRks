#pragma once
#include "FX/Niagara/Scheduler/LaunchSettings.h"
#include "World/DFUIAble.h"

#include "GenericFireworkLauncher.generated.h"

UCLASS(BlueprintType, Blueprintable)
class FIREVRKS_API AGenericFireworkLauncher : public ADFUIAble
{
	GENERATED_BODY()

public:
	virtual void OpenUI() override;

	AGenericFireworkLauncher();

	UFUNCTION(BlueprintNativeEvent)
	void DoOpenUI();


	UFUNCTION(BlueprintCallable)
	void Fire(ULaunchSettings* Settings);
};
