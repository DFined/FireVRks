#include "FX/Niagara/SystemSettings/FormalParameter/ValueEqualsPredicate.h"

template <class ValueType>
bool ValueEqualsPredicate<ValueType>::Check(ParameterValueContext* Context)
{
	return Parameter->GetValue(Context) == Value;
}

template <class ValueType>
ValueEqualsPredicate<ValueType>* ValueEqualsPredicate<ValueType>::Of(FormalParameter<ValueType>* Parameter, ValueType Val)
{
	return new ValueEqualsPredicate(Parameter, Val); 
}
