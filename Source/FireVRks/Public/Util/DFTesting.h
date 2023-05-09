#pragma once
#include "UI/lib/Container/DFUIContainer.h"
#include "UI/ParameterIntegration/ParameterInputUI.h"
#include "DFTesting.generated.h"

UCLASS(Abstract)
class UDFTesting : public UObject
{
public:
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable)
	static UParameterInputUI* MockParameters(UPanelWidget* Outer);

};
