#pragma once
#include "ParameterValueContext.h"

/**
 * Parameter value context which emulates binding outer keys onto inner keys and must be supplied with a primary context which to emulate as outers
 */
class BindingParameterValueContext : public ParameterValueContext
{
public:
	virtual AbstractParameterValue* GetInternal(FGuid ParameterId, DFType Type) override;

private:
	TMap<FGuid, FGuid> Bindings = TMap<FGuid, FGuid>();
	ParameterValueContext& PrimaryContext; 
public:
	
	explicit BindingParameterValueContext(ParameterValueContext& PrimaryContext, bool Managed)
		: PrimaryContext(PrimaryContext), ParameterValueContext(Managed)
	{
	}
};

