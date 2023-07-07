#pragma once
#include "AbstractFormalParameter.h"
#include "BlockCompoundParameter.h"
#include "FX/Niagara/SystemSettings/ParameterValues/ListParameterValue.h"

class ListFormalParameter : public AbstractFormalParameter
{
	ListParameterValue DefaultValue = ListParameterValue(true);

	BlockCompoundParameter* ChildType = nullptr;
public:
	virtual AbstractParameterValue* GetDefault() override;

	ListFormalParameter(const FGuid& GUID, BlockCompoundParameter* ChildType, FString& Name, bool IsRequired, bool bManaged)
		: AbstractFormalParameter(GUID, Name, DFType::LIST_BLOCK_PARAMETER, IsRequired, bManaged), ChildType(ChildType)
	{
	}

	ListFormalParameter(FString Name, BlockCompoundParameter* ChildType, bool IsRequired, bool bManaged)
		: AbstractFormalParameter(FGuid::NewGuid(), Name, DFType::LIST_BLOCK_PARAMETER, IsRequired, bManaged), ChildType(ChildType)
	{
	}

	virtual ~ListFormalParameter() override;

	BlockCompoundParameter* GetChildType() const;
};

