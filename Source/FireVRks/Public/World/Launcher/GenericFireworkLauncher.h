#pragma once
#include "FX/Niagara/System/SystemAndContext.h"
#include "World/DFUIAble.h"
#include "World/UFireworkShellBase.h"

#include "GenericFireworkLauncher.generated.h"

UCLASS(BlueprintType, Blueprintable)
class AGenericFireworkLauncher : public ADFUIAble
{
	GENERATED_BODY()

public:
	virtual void OpenUI() override;

	AGenericFireworkLauncher();

	UFUNCTION(BlueprintNativeEvent)
	void DoOpenUI();


	UFUNCTION(BlueprintCallable)
	AFireworkShellBase* Fire(USystemAndContext* SystemAndContext, float Delay, float Lifetime, float Velocity);
};
