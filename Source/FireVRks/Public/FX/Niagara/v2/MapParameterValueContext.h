#pragma once
#include "ParameterValueContext.h"
#include "Util/DFU.h"
#include "MapParameterValueContext.generated.h"
class UDFId;

UCLASS()
class FIREVRKS_API UMapParameterValueContext : public UParameterValueContext
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<UDFId*, UAbstractParameterValue*> Map;
public:
	virtual UAbstractParameterValue* Get(UAbstractFormalParameter* Parameter) override;

	virtual void SetValue(UAbstractFormalParameter* Parameter, UAbstractParameterValue* Value) override;
	void SetValue(UDFId* Parameter, UAbstractParameterValue* Value);

	DF_NEW(UMapParameterValueContext)
};
