#include "FX/Niagara/SystemSettings/InstanceParameter/ParameterValueContext.h"

#include "FX/Niagara/SystemSettings/FormalParameter/AbstractFormalParameter.h"

AbstractParameterValue* ParameterValueContext::Get(AbstractFormalParameter* Parameter)
{
	return GetById(Parameter->GetGUID(), Parameter->GetType(), Parameter->GetDefault());
}


AbstractParameterValue* ParameterValueContext::GetById(FGuid ParameterId, DFType Type, AbstractParameterValue* Default)
{
	auto Value = GetInternal(ParameterId, Type);
	if (Value)
	{
		if (Value->GetType() != Type)
		{
			return nullptr;
		}
		return Value;
	}
	return SetValue(ParameterId, Default);
}

DFType ParameterValueContext::GetType()
{
	return DFType::NONE;
}

