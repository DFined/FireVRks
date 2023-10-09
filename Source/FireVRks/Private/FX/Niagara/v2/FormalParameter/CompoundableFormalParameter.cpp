#include "FX/Niagara/v2/FormalParameter/CompoundableFormalParameter.h"

#include "FX/Niagara/v2/ParamUtil.h"
#include "FX/Niagara/v2/ValueEqualsPredicate.h"
#include "FX/Niagara/v2/FormalParameter/BoolFormalParameter.h"


template <class ParamType, typename ValueType>
UCompoundableFormalParameter* UCompoundableFormalParameter::New(UObject* Outer, FString ValueName, bool Required, ValueType DefaultValue)
{
	auto Param = NewObject<UCompoundableFormalParameter>(Outer, StaticClass());
	CommonInit<ParamType, ValueType>(Outer, Param, ValueName, Required, DefaultValue, DefaultValue, false);
	return Param;
}

template <class ParamType, typename ValueType>
UCompoundableFormalParameter* UCompoundableFormalParameter::New(UDFAnchor* Outer, FString ValueName, bool Required, float DefaultMin, float DefaultMax)
{
	auto Param = NewObject<UCompoundableFormalParameter>(Outer, StaticClass());
	CommonInit<ParamType, ValueType>(Outer, Param, ValueName, Required, DefaultMin, DefaultMax, false);
	return Param;
}

UBlockFormalParameter* UCompoundableFormalParameter::GetBlockParam()
{
	return BlockParam;
}

template <class Outer, typename Inner>
Inner UCompoundableFormalParameter::GetMin(UParameterValueContext* Context)
{
	auto Param = Context->Get(SelectorParam) ? Context->Get(MinParam) : Context->Get(DefaultParam);
	return UParamUtil::GetTypedValue<Outer, Inner>(Param);
}

template <class Outer, typename Inner>
Inner UCompoundableFormalParameter::GetMax(UParameterValueContext* Context)
{
	auto Param = Context->Get(SelectorParam) ? Context->Get(MaxParam) : Context->Get(DefaultParam);
	return UParamUtil::GetTypedValue<Outer, Inner>(Param);
}

template <class ParamType, typename ValueType>
void UCompoundableFormalParameter::CommonInit(UObject* Outer, UCompoundableFormalParameter* Param, FString ValueName, bool Required,
	ValueType Min, ValueType Max, bool Expanded)
{
	Param->BlockParam = UParamUtil::Setup(ValueName, Required, UBlockFormalParameter::New(Outer, true));
	Param->DefaultParam = UParamUtil::Setup(ValueName, true, ParamType::New(Outer, Min));
	Param->MinParam = UParamUtil::Setup("Minimum " + ValueName, true, ParamType::New(Outer, Min));
	Param->MaxParam = UParamUtil::Setup("Maximum " + ValueName, true, ParamType::New(Outer, Max));
	Param->SelectorParam = UParamUtil::Global<UBoolFormalParameter, bool>("Randomize " + ValueName, true, Expanded);

	Param->MinParam->SetPredicate(new ValueEqualsPredicate<BOOL_VALUE>(Param->SelectorParam, true));
	Param->MaxParam->SetPredicate(new ValueEqualsPredicate<BOOL_VALUE>(Param->SelectorParam, true));
	Param->DefaultParam->SetPredicate(new ValueEqualsPredicate<BOOL_VALUE>(Param->SelectorParam, false));

	Param->BlockParam->Add(Param->SelectorParam);
	Param->BlockParam->Add(Param->DefaultParam);
	Param->BlockParam->Add(Param->MinParam);
	Param->BlockParam->Add(Param->MaxParam);
}
