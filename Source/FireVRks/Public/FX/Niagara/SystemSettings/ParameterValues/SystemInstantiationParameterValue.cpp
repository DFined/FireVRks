#include "SystemInstantiationParameterValue.h"

DFType SystemInstantiationParameterValue::GetType()
{
	return DFType::SYSTEM_INSTANTIATION_PARAMETER;
}

SystemInstantiationParameterValue::~SystemInstantiationParameterValue()
{
	SafeRelease(Context);
}
