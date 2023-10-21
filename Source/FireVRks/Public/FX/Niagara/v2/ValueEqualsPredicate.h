#pragma once
#include "ParameterPredicate.h"
#include "ParamUtil.h"
#include "FormalParameter/AbstractFormalParameter.h"

template <class OuterType, typename ValueType>
class ValueEqualsPredicate : public ParameterPredicate
{
	UAbstractFormalParameter* Parameter;
	ValueType Value;

public:
	explicit ValueEqualsPredicate(UAbstractFormalParameter* Parameter, ValueType Val)
		: Parameter(Parameter), Value(Val)
	{
	}

	virtual bool Check(UParameterValueContext* Context) override
	{
		return UParamUtil::GetTypedValue<OuterType, ValueType>(Context->Get(Parameter)) == Value;
	};
};
