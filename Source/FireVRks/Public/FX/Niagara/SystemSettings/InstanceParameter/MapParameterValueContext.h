#pragma once
#include "ParameterValueContext.h"
#include "FX/Niagara/SystemSettings/ParameterValues/AbstractParameterValue.h"

/**
 * Simple implementation of a value-context as a Map
 */
class MapParameterValueContext : public TMap<FGuid, AbstractParameterValue*>, public ParameterValueContext
{
public:
	MapParameterValueContext(bool bManaged) : TMap(), ParameterValueContext(bManaged)
	{
	}

	virtual ~MapParameterValueContext() override;

	virtual AbstractParameterValue* GetInternal(FGuid ParameterId, DFType Type) override;

	virtual AbstractParameterValue* SetValue(FGuid ParamId, AbstractParameterValue* Value) override;
	void RemoveParamFromMap(FGuid Param);
};
