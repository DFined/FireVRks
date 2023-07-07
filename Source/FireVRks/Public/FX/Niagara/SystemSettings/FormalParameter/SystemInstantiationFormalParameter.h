#pragma once
#include "AbstractFormalParameter.h"

class SystemInstantiationFormalParameter : public AbstractFormalParameter
{	
public:
	SystemInstantiationFormalParameter(const FGuid& GUID, FString Name, bool IsRequired)
		: AbstractFormalParameter(GUID, Name, DFType::SYSTEM_INSTANTIATION_PARAMETER, IsRequired, true)
	{
	}

	SystemInstantiationFormalParameter(FString Name, bool IsRequired)
		: AbstractFormalParameter(FGuid::NewGuid(), Name, DFType::SYSTEM_INSTANTIATION_PARAMETER, IsRequired, true)
	{
	}

	virtual AbstractParameterValue* GetDefault() override;	
};
