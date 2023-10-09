#pragma once
#include "ParameterValueContext.h"
#include "MapParameterValueContext.generated.h"

UCLASS()
class FIREVRKS_API UMapParameterValueContext : public UParameterValueContext, public TMap<UDFId*, UAbstractParameterValue*>
{
	GENERATED_BODY()
public:
	virtual UAbstractParameterValue* Get(UAbstractFormalParameter* Parameter) override;

	virtual void SetValue(UAbstractFormalParameter* Parameter, UAbstractParameterValue* Value) override;

	static UMapParameterValueContext* New(UObject* Outer)
	{
		return NewObject<UMapParameterValueContext>(Outer, StaticClass());
	}
};
