#pragma once
#include "FX/Niagara/v2/FormalParameter/BlockFormalParameter.h"
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
	static UCompoundableFormalParameter* New(UObject* Outer, FString ValueName, bool Required, ValueType DefaultValue);
	template <class ParamType, typename ValueType>
	static UCompoundableFormalParameter* New(UDFAnchor* Outer, FString ValueName, bool bRequired, float DefaultMin, float DefaultMax);
	
	template <class ParamType, typename ValueType>
	static void CommonInit(UObject* Outer, UCompoundableFormalParameter* Param, FString ValueName, bool Required, ValueType Min, ValueType Max, bool Expanded);

	UBlockFormalParameter* GetBlockParam();

	template <class Outer, typename Inner>
	Inner GetMin(UParameterValueContext* Context);
	template <class Outer, typename Inner>
	Inner GetMax(UParameterValueContext* Context);	
};

