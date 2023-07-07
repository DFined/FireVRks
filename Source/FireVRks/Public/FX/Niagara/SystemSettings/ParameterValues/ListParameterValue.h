#pragma once
#include "AbstractParameterValue.h"
#include "FX/Niagara/SystemSettings/FormalParameter/BlockCompoundParameter.h"

class ListParameterValue : public AbstractParameterValue 
{
	TArray<ParameterValueContext*> Values;
public:
	ListParameterValue(bool bManaged) : AbstractParameterValue(bManaged), Values(TArray<ParameterValueContext*>())
	{
	}

	void AddValue(ParameterValueContext* Param)
	{
		Param->Depend();
		Values.Add(Param);
	}

	TArray<ParameterValueContext*>& GetValues(){
		return Values;
	}

	virtual ~ListParameterValue() override;

	virtual DFType GetType() override;
};

