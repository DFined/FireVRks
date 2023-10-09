#include "MapParameterValueContext.h"

#include "FormalParameter/AbstractFormalParameter.h"

UAbstractParameterValue* UMapParameterValueContext::Get(UAbstractFormalParameter* Parameter)
{
	auto Id = Parameter->GetId();
	if (this->Contains(Id))
	{
		auto Val = this->Find(Id);
		if (Val)
		{
			return *Val;
		}
	}
	auto Val = Parameter->DefaultValue();
	this->Add(Id, Val);
	return Val;
}

void UMapParameterValueContext::SetValue(UAbstractFormalParameter* Parameter, UAbstractParameterValue* Value)
{
	this->Add(Parameter->GetId(), Value);
}
