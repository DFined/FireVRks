#pragma once
#include "ParameterValue/AbstractParameterValue.h"
#include "ParameterValueContext.generated.h"

class UBindingParameterValueContext;
class UAbstractFormalParameter;

UCLASS(Abstract)
class FIREVRKS_API UParameterValueContext : public UObject
{
	GENERATED_BODY()

public:
	virtual UAbstractParameterValue* Get(UAbstractFormalParameter* Parameter) PURE_VIRTUAL("Get", return nullptr;);
	virtual void SetValue(UAbstractFormalParameter* Parameter, UAbstractParameterValue* Value) PURE_VIRTUAL("SetValue",);

	static UBindingParameterValueContext* NewContextFrom(UParameterValueContext* Context);
};
