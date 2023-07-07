#pragma once

class ParameterValueContext;

class ParameterPredicate
{
public:
	ParameterPredicate() = default;
	virtual ~ParameterPredicate() = default;
	virtual bool Check(ParameterValueContext* Context) = 0;
};
