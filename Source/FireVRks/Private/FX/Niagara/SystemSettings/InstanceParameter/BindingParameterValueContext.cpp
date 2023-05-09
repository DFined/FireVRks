#include "FX/Niagara/SystemSettings/InstanceParameter/BindingParameterValueContext.h"


AbstractParameterValue* BindingParameterValueContext::GetInternal(FGuid ParameterId, DFType Type)
{
	if (const auto MappedId = Bindings.Find(ParameterId))
	{
		ParameterId = *MappedId;
	}
	return PrimaryContext.GetById(ParameterId, Type, __nullptr);
}
