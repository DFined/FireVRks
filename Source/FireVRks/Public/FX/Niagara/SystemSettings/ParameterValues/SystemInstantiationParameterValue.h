#pragma once
#include "FX/Niagara/System/EffectSystem.h"
#include "FX/Niagara/SystemSettings/FormalParameter/AbstractFormalParameter.h"

class SystemInstantiationParameterValue : public AbstractParameterValue
{
	UEffectSystem* System;
	ParameterValueContext* Context;
public:
	explicit SystemInstantiationParameterValue(UEffectSystem* System, ParameterValueContext* Context, bool bManaged)
		: AbstractParameterValue(bManaged), System(System), Context(Context)
	{
		Context->Depend();
	}

	virtual DFType GetType() override;

	ParameterValueContext* GetContext() const
	{
		return Context;
	}

	UEffectSystem* GetSystem() const
	{
		return System;
	}

	virtual ~SystemInstantiationParameterValue() override;
};
