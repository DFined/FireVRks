#pragma once
#include "FormalParameter.h"
#include "FX/Niagara/SystemSettings/Enums/EnumLike.h"

class EnumFormalParameter : public FormalParameter<EnumLikeValue*>
{
	EnumLike* EnumType;
	
public:
	EnumFormalParameter(const FString& GUID, const FString& Name, bool IsRequired, EnumLike* EType, bool bManaged)
		: FormalParameter(GUID, Name, DFType::TYPED_ENUM_PARAMETER, IsRequired, EType->GetDefaultValue(), bManaged), EnumType(EType)
	{
	}

	EnumFormalParameter(const FString& Name, bool IsRequired, EnumLike* EType, bool bManaged)
		: FormalParameter(DFType::TYPED_ENUM_PARAMETER, Name, IsRequired, EType->GetDefaultValue(), bManaged), EnumType(EType)
	{
	}

	EnumLike* GetEnumType() const
	{
		return EnumType;
	}
};
