#include "FX/Niagara/SystemSettings/ParameterValues/ListParameterValue.h"

ListParameterValue::~ListParameterValue()
{
	for(ParameterValueContext* Parameter: Values)
	{
		Parameter->Release();
		if(!Parameter->IsDependedOn())
		{
			delete(Parameter);
		}
	}
}

DFType ListParameterValue::GetType()
{
	return DFType::LIST_BLOCK_PARAMETER;
}
