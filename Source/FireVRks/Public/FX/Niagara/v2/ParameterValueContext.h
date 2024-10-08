#pragma once
#include "ParameterValueContext.generated.h"

class UBindingParameterValueContext;
struct FDFId;
class UAbstractParameterValue;
class UAbstractFormalParameter;

UCLASS(Abstract)
class FIREVRKS_API UParameterValueContext : public UObject
{
	GENERATED_BODY()

public:
	virtual UAbstractParameterValue* Get(UAbstractFormalParameter* Parameter) PURE_VIRTUAL("Get", return nullptr;)
	virtual UParameterValueContext* Clone(UObject* Parent) PURE_VIRTUAL("Clone", return nullptr;)
	static UParameterValueContext* FromJson(TSharedPtr<FJsonObject> Json, UObject* Outer, TMap<FDFId, UAbstractFormalParameter*> Outers);
	virtual void SetValue(UAbstractFormalParameter* Parameter, UAbstractParameterValue* Value) PURE_VIRTUAL("SetValue",);

	static UBindingParameterValueContext* NewContextFrom(UParameterValueContext* Context);

	virtual TSharedPtr<FJsonObject> ToJson() PURE_VIRTUAL("ToJson", return TSharedPtr<FJsonObject>(nullptr););
};
