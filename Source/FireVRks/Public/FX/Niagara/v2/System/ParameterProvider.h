#pragma once
#include "FX/Niagara/v2/FormalParameter/AbstractFormalParameter.h"
#include "Util/DFId.h"

class ParameterProvider
{
public:
	virtual ~ParameterProvider() = default;
	virtual TMap<UDFId*, UAbstractFormalParameter*>* GetOuterParameters() = 0;
	virtual void GetOuterParametersInOrder(TArray<UAbstractFormalParameter*>& Result) = 0;
};
