#include "FX/Niagara/v2/ValueEqualsPredicate.h"

#include "FX/Niagara/v2/ParamUtil.h"


template <class OuterType, typename ValueType>
bool ValueEqualsPredicate<OuterType, ValueType>::Check(UParameterValueContext* Context)
{
	return UParamUtil::GetTypedValue<OuterType, ValueType>(Context->Get(Parameter)) == Value;
}

