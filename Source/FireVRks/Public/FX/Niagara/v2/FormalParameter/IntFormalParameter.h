#pragma once
#include "AbstractFormalParameter.h"
#include "FX/Niagara/v2/ParamUtil.h"
#include "FX/Niagara/v2/ParameterValue/IntParameterValue.h"
#include "IntFormalParameter.generated.h"

UCLASS()
class FIREVRKS_API UIntFormalParameter : public UAbstractFormalParameter
{
	GENERATED_BODY()
	
public:
	static UIntFormalParameter* New(UObject* Outer, int DefaultValue);

	DF_PARAMETER_GETTER(UIntParameterValue, int);
};
