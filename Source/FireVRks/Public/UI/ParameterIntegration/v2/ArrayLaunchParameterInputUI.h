#pragma once
#include "ParameterInputUI.h"
#include "UI/DFUIUtil.h"
#include "ArrayLaunchParameterInputUI.generated.h"

UCLASS(Blueprintable, BlueprintType)
class FIREVRKS_API  UArrayLaunchParameterInputUI : public UParameterInputUI
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Launch(FString ArrayName) const;

	UFUNCTION(BlueprintCallable)
	static UArrayLaunchParameterInputUI* InstanceEmpty(UPanelWidget* Widget);
	
	UFUNCTION(BlueprintCallable)
	static UArrayLaunchParameterInputUI* Instance(UPanelWidget* Widget, UParameterValueContext* fContext);
};
