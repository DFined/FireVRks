#pragma once
#include "FX/Niagara/SystemSettings/FormalParameter/ParameterPredicate.h"

class TruePredicate : public ParameterPredicate
{
public:
	TruePredicate():ParameterPredicate(){};
	virtual bool Check(ParameterValueContext* Context) override;
};
