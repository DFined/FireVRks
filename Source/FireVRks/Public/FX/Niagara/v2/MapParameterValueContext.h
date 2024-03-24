#pragma once
#include "ParameterValueContext.h"
#include "Util/DFU.h"
#include "Util/DFId.h"
#include "MapParameterValueContext.generated.h"

UCLASS()
class FIREVRKS_API UMapParameterValueContext : public UParameterValueContext
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<FDFId, UAbstractParameterValue*> Map;
public:
	virtual UAbstractParameterValue* Get(UAbstractFormalParameter* Parameter) override;

	virtual void SetValue(UAbstractFormalParameter* Parameter, UAbstractParameterValue* Value) override;
	void SetValue(FDFId Parameter, UAbstractParameterValue* Value);

	DF_NEW(UMapParameterValueContext)

	virtual TSharedPtr<FJsonObject> ToJson() override;

	virtual UParameterValueContext* Clone(UObject* Parent) override;
};
