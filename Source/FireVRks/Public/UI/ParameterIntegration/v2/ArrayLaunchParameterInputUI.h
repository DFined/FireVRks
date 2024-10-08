#pragma once
#include "ParameterInputUI.h"
#include "ArrayLaunchParameterInputUI.generated.h"

UCLASS(Blueprintable, BlueprintType)
class FIREVRKS_API  UArrayLaunchParameterInputUI : public UParameterInputUI
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Launch(float Delay, bool Test);

	UFUNCTION(BlueprintCallable)
	static UArrayLaunchParameterInputUI* InstanceEmpty(UPanelWidget* Widget);
	
	UFUNCTION(BlueprintCallable)
	static UArrayLaunchParameterInputUI* Instance(UPanelWidget* Widget, UParameterValueContext* fContext);
	
};
