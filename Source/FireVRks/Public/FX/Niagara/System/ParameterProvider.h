#pragma once
#include "FX/Niagara/SystemSettings/FormalParameter/AbstractFormalParameter.h"

class ParameterProvider
{
public:
	virtual ~ParameterProvider() = default;
	virtual TArray<AbstractFormalParameter*> GetOuterParameters() {return TArray<AbstractFormalParameter*>();}
};
