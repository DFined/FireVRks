#include "FX/Niagara/SystemSettings/FormalParameter/AbstractFormalParameter.h"

DFType AbstractFormalParameter::GetType()
{
	return ValueType;
}

AbstractParameterValue* AbstractFormalParameter::GetDefault()
{
	return __nullptr;
}

AbstractFormalParameter::~AbstractFormalParameter()
{
	if (DisplayPredicate) { delete DisplayPredicate; }
}
