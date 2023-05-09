#include "FX/Niagara/SystemSettings/FormalParameter/FormalParameter.h"

template <typename Type>
AbstractParameterValue* FormalParameter<Type>::GetDefault()
{
	return AbstractValue;
}

template <typename Type>
FormalParameter<Type>::~FormalParameter()
{
	delete(AbstractValue);
}
