#include "FX/Niagara/SystemSettings/InstanceParameter/MapParameterValueContext.h"

#include "FX/Niagara/SystemSettings/ParameterValues/AbstractParameterValue.h"

MapParameterValueContext::~MapParameterValueContext()
{
	TArray<FGuid> Keys = TArray<FGuid>();
	this->GetKeys(Keys);
	for (FGuid Key : Keys)
	{
		RemoveParamFromMap(Key);
	}
}

AbstractParameterValue* MapParameterValueContext::GetInternal(FGuid ParameterId, DFType Type)
{
	auto Val = Find(ParameterId);
	return Val ? *Val : nullptr;
}

AbstractParameterValue* MapParameterValueContext::SetValue(FGuid ParamId, AbstractParameterValue* Value)
{
	if (Value)
	{
		if (this->Contains(ParamId))
		{
			RemoveParamFromMap(ParamId);
		}
		this->Add(ParamId, Value);
		Value->Depend();
		return Value;
	}
	return Value;
}

void MapParameterValueContext::RemoveParamFromMap(FGuid Param)
{
	auto Val = Find(Param);
	if (Val)
	{
		(*Val)->Release();
		if (!(*Val)->IsDependedOn())
		{
			delete(*Val);
		}
		this->Remove(Param);
	}
}
