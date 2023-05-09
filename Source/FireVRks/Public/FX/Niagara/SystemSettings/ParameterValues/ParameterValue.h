#pragma once
#include "AbstractParameterValue.h"

template <class ValueType>
class ParameterValue : public AbstractParameterValue
{
	ValueType Value;
	DFType Type;

public:
	ParameterValue(ValueType Value, DFType Type, bool Managed) : AbstractParameterValue(Managed), Value(Value), Type(Type)
	{
	}

	ValueType& Get() { return Value; }
	virtual DFType GetType() override;
};
