#pragma once
#include "FormalParameter.h"
#include "ParameterPredicate.h"

template <class ValueType>
class ValueEqualsPredicate : public ParameterPredicate
{
	FormalParameter<ValueType>* Parameter;
	ValueType Value;
	
	explicit ValueEqualsPredicate(FormalParameter<ValueType>* Parameter, ValueType Val)
		: Parameter(Parameter), Value(Val)
	{
	}
public:

	virtual bool Check(ParameterValueContext* Context) override;

	static ValueEqualsPredicate* Of(FormalParameter<ValueType>* Parameter, ValueType Val);
};

