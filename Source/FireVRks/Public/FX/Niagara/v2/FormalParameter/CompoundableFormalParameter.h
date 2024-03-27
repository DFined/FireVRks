#pragma once
#include "BoolFormalParameter.h"
#include "FX/Niagara/v2/ParamUtil.h"
#include "FX/Niagara/v2/ValueEqualsPredicate.h"
#include "FX/Niagara/v2/FormalParameter/BlockFormalParameter.h"
#include "FX/Niagara/v2/ParameterValue/BoolParameterValue.h"
#include "Util/DFAnchor.h"
#include "CompoundableFormalParameter.generated.h"

/**
 * Utility class which represents semi-compound parameters that consist of a randomize selector, a default parameter and min-max values 
 */
UCLASS()
class FIREVRKS_API UCompoundableFormalParameter : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	UBlockFormalParameter* BlockParam;
	UPROPERTY()
	UAbstractFormalParameter* DefaultParam;
	UPROPERTY()
	UAbstractFormalParameter* MinParam;
	UPROPERTY()
	UAbstractFormalParameter* MaxParam;
	UPROPERTY()
	UAbstractFormalParameter* SelectorParam;

public:
	template <class ParamType, typename ValueType>
	static UCompoundableFormalParameter* New(UObject* Outer, FString ValueName, bool Required, ValueType DefaultValue)
	{
		auto Param = NewObject<UCompoundableFormalParameter>(Outer, StaticClass());
		CommonInit<ParamType, ValueType>(Outer, Param, ValueName, Required, DefaultValue, DefaultValue, false);
		return Param;
	}

	template <class ParamType, typename ValueType>
	static UCompoundableFormalParameter* New(UDFAnchor* Outer, FString ValueName, bool bRequired, float DefaultMin,
											 float DefaultMax)
	{
		auto Param = NewObject<UCompoundableFormalParameter>(Outer, StaticClass());
		CommonInit<ParamType, ValueType>(Outer, Param, ValueName, bRequired, DefaultMin, DefaultMax, false);
		return Param;
	}

	template <class ParamType, typename ValueType>
	static void CommonInit(UObject* Outer, UCompoundableFormalParameter* Param, FString ValueName, bool Required,
						   ValueType Min, ValueType Max, bool Expanded)
	{
		auto IdPostfix =  ValueName.Replace(*FString(" "), *FString(""));

		Param->BlockParam = UParamUtil::Setup(ValueName, Required, UBlockFormalParameter::New(Outer, true));
		Param->DefaultParam = UParamUtil::Setup("{BUILTINS_PARAMETER_NAME}_" + IdPostfix, ValueName, true, ParamType::New(Outer, Min));
		Param->MinParam = UParamUtil::Setup("{BUILTINS_PARAMETER_NAME}_MIN_" + IdPostfix, "Minimum " + ValueName, true, ParamType::New(Outer, Min));
		Param->MaxParam = UParamUtil::Setup("{BUILTINS_PARAMETER_NAME}_MAX_" + IdPostfix, "Maximum " + ValueName, true, ParamType::New(Outer, Max));
		Param->SelectorParam = UParamUtil::Global<UBoolFormalParameter, bool>("Randomize " + ValueName, true, Expanded);

		Param->MinParam->SetPredicate(new ValueEqualsPredicate<BOOL_VALUE>(Param->SelectorParam, true));
		Param->MaxParam->SetPredicate(new ValueEqualsPredicate<BOOL_VALUE>(Param->SelectorParam, true));
		Param->DefaultParam->SetPredicate(new ValueEqualsPredicate<BOOL_VALUE>(Param->SelectorParam, false));

		Param->BlockParam->Add(Param->SelectorParam);
		Param->BlockParam->Add(Param->DefaultParam);
		Param->BlockParam->Add(Param->MinParam);
		Param->BlockParam->Add(Param->MaxParam);
	}

	UBlockFormalParameter* GetBlockParam();

	template <class Outer, typename Inner>
	Inner GetMin(UParameterValueContext* Context)
	{
		auto Param = UParamUtil::GetTypedValue<UBoolParameterValue, bool>(Context->Get(SelectorParam))
						 ? Context->Get(MinParam)
						 : Context->Get(DefaultParam);
		return UParamUtil::GetTypedValue<Outer, Inner>(Param);
	}

	template <class Outer, typename Inner>
	Inner GetMax(UParameterValueContext* Context)
	{
		auto Param = UParamUtil::GetTypedValue<UBoolParameterValue, bool>(Context->Get(SelectorParam))
						 ? Context->Get(MaxParam)
						 : Context->Get(DefaultParam);
		return UParamUtil::GetTypedValue<Outer, Inner>(Param);
	}
};
