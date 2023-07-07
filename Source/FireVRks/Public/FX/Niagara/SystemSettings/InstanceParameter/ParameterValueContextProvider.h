#pragma once
#include "ParameterValueContext.h"
#include "ParameterValueContextProvider.generated.h"

UCLASS(BlueprintType)
class UParameterValueContextProvider : public UObject
{
	GENERATED_BODY()
public:
	virtual ParameterValueContext* Get() PURE_VIRTUAL("Get",return nullptr;);
};
