#pragma once
#include "FX/Niagara/v2/FormalParameter/AbstractFormalParameter.h"

class ParameterProvider
{
public:
	virtual ~ParameterProvider() = default;
	virtual TArray<UAbstractFormalParameter*>* GetOuterParameters() {return nullptr;}
};
