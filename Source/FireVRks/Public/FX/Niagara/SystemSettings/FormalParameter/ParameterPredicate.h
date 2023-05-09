#pragma once
#include "FX/Niagara/SystemSettings/InstanceParameter/ParameterValueContext.h"

class ParameterPredicate
{
public:
	ParameterPredicate() = default;
	virtual ~ParameterPredicate() = default;
	virtual bool Check(ParameterValueContext* Context) = 0;
};
