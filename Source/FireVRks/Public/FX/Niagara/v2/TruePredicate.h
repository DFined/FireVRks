#pragma once
#include "ParameterPredicate.h"

class TruePredicate : public ParameterPredicate
{
public:
	TruePredicate():ParameterPredicate(){};
	virtual bool Check(UParameterValueContext* Context) override;
};
