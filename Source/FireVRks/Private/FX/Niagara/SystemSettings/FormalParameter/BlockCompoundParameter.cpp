#include "FX/Niagara/SystemSettings/FormalParameter/BlockCompoundParameter.h"

AbstractParameterValue* BlockCompoundParameter::GetDefault()
{
	return &Default;
}

void BlockCompoundParameter::AddChild(AbstractFormalParameter* Parameter)
{
	ChildParameters.Add(Parameter);
	Parameter->Depend();
}

TArray<AbstractFormalParameter*> BlockCompoundParameter::GetChildParameters() const
{
	return ChildParameters;
}

BlockCompoundParameter::~BlockCompoundParameter()
{
	for(AbstractFormalParameter* Param: ChildParameters)
	{
		Param->Release();
		if(!Param->IsDependedOn())
		{
			delete(Param);
		}
	}
}
