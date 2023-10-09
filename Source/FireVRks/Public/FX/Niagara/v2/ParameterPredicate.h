#pragma once
#include "ParameterValueContext.h"

class ParameterPredicate
{
public:
	ParameterPredicate() = default;
	virtual ~ParameterPredicate() = default;
	virtual bool Check(UParameterValueContext* Context) = 0;
};
