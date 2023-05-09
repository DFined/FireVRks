#pragma once
#include "ParamUtilObject.h"
#include "FX/Niagara/SystemSettings/ParameterValues/ParameterValue.h"

/**
 * Due to unreal not supporting templates, parameters have a lot of switch-case type code required, which includes UI stuff that doesn't belong in a data class.
 * This is a class for tidying it all up
 */
class ParameterTypingUtil
{
public:
	static ParamUtilObject INT_PARAM_UTIL_OBJECT;
	static ParamUtilObject FLOAT_PARAM_UTIL_OBJECT;
	static ParamUtilObject VECTOR_PARAM_UTIL_OBJECT;
	static ParamUtilObject BOOL_PARAM_UTIL_OBJECT;
	static ParamUtilObject ENUM_PARAM_UTIL_OBJECT;
	static ParamUtilObject COMPOUND_PARAM_UTIL_OBJECT;

	static ParamUtilObject* GetParamUtil(DFType ParamType);

	template <class ValueType>
	static ParameterValue<ValueType>* ToValue(AbstractParameterValue* Value);

};

