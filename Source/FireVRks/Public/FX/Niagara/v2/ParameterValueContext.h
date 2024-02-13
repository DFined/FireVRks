#pragma once
#include "ParameterValueContext.generated.h"

class UAbstractParameterValue;
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

	virtual TSharedPtr<FJsonObject> ToJson() PURE_VIRTUAL("ToJson", return TSharedPtr<FJsonObject>(nullptr););

	static UParameterValueContext* FromJson(TSharedPtr<FJsonObject> Json, UObject* Outer);	
};
