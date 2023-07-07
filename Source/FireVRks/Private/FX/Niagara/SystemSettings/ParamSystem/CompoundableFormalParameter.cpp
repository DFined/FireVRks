#include "FX/Niagara/SystemSettings/ParamSystem/CompoundableFormalParameter.h"

#include "FX/Niagara/SystemSettings/FormalParameter/ValueEqualsPredicate.h"


template <class ValueType>
CompoundableFormalParameter<ValueType>::CompoundableFormalParameter(FString ValueName, DFType Type, bool Required, ValueType DefaultValue) :
	BlockParam(BlockCompoundParameter(ValueName, Required, true, true)),
	DefaultParam(FormalParameter(Type, ValueName, true, DefaultValue, true)),
	MinParam(FormalParameter(Type, "Minimum " + ValueName, true, DefaultValue, true)),
	MaxParam(FormalParameter(Type, "Maximum " + ValueName, true, DefaultValue, true)),
	SelectorParam(FormalParameter(DFType::TYPED_BOOL_PARAMETER, "Randomize " + ValueName, true, false, true))
{
	MinParam.SetDisplayPredicate(ValueEqualsPredicate<bool>::Of(&SelectorParam, true));
	MaxParam.SetDisplayPredicate(ValueEqualsPredicate<bool>::Of(&SelectorParam, true));
	DefaultParam.SetDisplayPredicate(ValueEqualsPredicate<bool>::Of(&SelectorParam, false));

	BlockParam.AddChild(&SelectorParam);
	BlockParam.AddChild(&DefaultParam);
	BlockParam.AddChild(&MinParam);
	BlockParam.AddChild(&MaxParam);
}

template <class ValueType>
CompoundableFormalParameter<ValueType>::CompoundableFormalParameter(FString ValueName, DFType Type, bool Required, ValueType DefaultValueMin,
	ValueType DefaultValueMax) :
	BlockParam(BlockCompoundParameter(ValueName, Required, true, true)),
	DefaultParam(FormalParameter(Type, ValueName, true, DefaultValueMin, true)),
	MinParam(FormalParameter(Type, "Minimum " + ValueName, true, DefaultValueMin, true)),
	MaxParam(FormalParameter(Type, "Maximum " + ValueName, true, DefaultValueMax, true)),
	SelectorParam(FormalParameter(DFType::TYPED_BOOL_PARAMETER, "Randomize " + ValueName, true, true, true))
{
	MinParam.SetDisplayPredicate(ValueEqualsPredicate<bool>::Of(&SelectorParam, true));
	MaxParam.SetDisplayPredicate(ValueEqualsPredicate<bool>::Of(&SelectorParam, true));
	DefaultParam.SetDisplayPredicate(ValueEqualsPredicate<bool>::Of(&SelectorParam, false));

	BlockParam.AddChild(&SelectorParam);
	BlockParam.AddChild(&DefaultParam);
	BlockParam.AddChild(&MinParam);
	BlockParam.AddChild(&MaxParam);
}

template <class ValueType>
BlockCompoundParameter* CompoundableFormalParameter<ValueType>::GetBlockParam()
{
	return &BlockParam;
}

template <class ValueType>
ValueType CompoundableFormalParameter<ValueType>::GetMin(ParameterValueContext* Context)
{
	return SelectorParam.GetValue(Context) ? MinParam.GetValue(Context) : DefaultParam.GetValue(Context);
}

template <class ValueType>
ValueType CompoundableFormalParameter<ValueType>::GetMax(ParameterValueContext* Context)
{
	return SelectorParam.GetValue(Context) ? MaxParam.GetValue(Context) : DefaultParam.GetValue(Context);
}
