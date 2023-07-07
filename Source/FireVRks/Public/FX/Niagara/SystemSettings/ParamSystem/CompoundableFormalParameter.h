#pragma once
#include "FX/Niagara/SystemSettings/FormalParameter/BlockCompoundParameter.h"
#include "FX/Niagara/SystemSettings/FormalParameter/FormalParameter.h"

/**
 * Utility class which represents semi-compound parameters that consist of a randomize selector, a default parameter and min-max values 
 */
template <class ValueType>
class CompoundableFormalParameter
{
	BlockCompoundParameter BlockParam;
	FormalParameter<ValueType> DefaultParam;
	FormalParameter<ValueType> MinParam;
	FormalParameter<ValueType> MaxParam;
	FormalParameter<bool> SelectorParam;
public:
	CompoundableFormalParameter(FString ValueName, DFType Type, bool Required, ValueType DefaultValue);
	CompoundableFormalParameter(FString ValueName, DFType Type, bool Required, ValueType DefaultValueMin, ValueType DefaultValueMax);

	BlockCompoundParameter* GetBlockParam();

	ValueType GetMin(ParameterValueContext* Context);

	ValueType GetMax(ParameterValueContext* Context);
};
