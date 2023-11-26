#include "FX/Niagara/v2/MapParameterValueContext.h"

#include "FX/Niagara/v2/FormalParameter/AbstractFormalParameter.h"

UAbstractParameterValue* UMapParameterValueContext::Get(UAbstractFormalParameter* Parameter)
{
	auto Id = Parameter->GetId();
	if (Map.Contains(Id))
	{
		auto Val = Map.Find(Id);
		if (Val)
		{
			return *Val;
		}
	}
	auto Val = Parameter->DefaultValue();
	Map.Add(Id, Val);
	return Val;
}

void UMapParameterValueContext::SetValue(UAbstractFormalParameter* Parameter, UAbstractParameterValue* Value)
{
	Map.Add(Parameter->GetId(), Value);
}

void UMapParameterValueContext::SetValue(UDFId* Parameter, UAbstractParameterValue* Value)
{
	Map.Add(Parameter, Value);
}
