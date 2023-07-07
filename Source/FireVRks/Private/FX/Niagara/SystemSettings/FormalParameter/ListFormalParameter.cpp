#include "FX/Niagara/SystemSettings/FormalParameter/ListFormalParameter.h"


AbstractParameterValue* ListFormalParameter::GetDefault()
{
	return &DefaultValue;
}

ListFormalParameter::~ListFormalParameter()
{
}

BlockCompoundParameter* ListFormalParameter::GetChildType() const
{
	return ChildType;
}

