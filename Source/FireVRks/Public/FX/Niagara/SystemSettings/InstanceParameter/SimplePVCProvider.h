#pragma once
#include "ParameterValueContextProvider.h"
#include "SimplePVCProvider.generated.h"

/**
 * Wrapper for PVC so that I can use it in UFunctions
 */
UCLASS(BlueprintType)
class USimplePVCProvider : public UParameterValueContextProvider
{
	GENERATED_BODY()

	ParameterValueContext* Context;
public:

	virtual ParameterValueContext* Get() override;

	void SetContext(ParameterValueContext* FContext)
	{
		this->Context = FContext;
	}

	static UParameterValueContextProvider* Of(ParameterValueContext* Context, UObject* Outer);
};
