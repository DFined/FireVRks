#include "FX/Niagara/SystemSettings/ParameterValues/ParameterValue.h"

template <class ValueType>
DFType ParameterValue<ValueType>::GetType()
{
	return Type;
}
