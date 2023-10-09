#include "FX/Niagara/v2/FormalParameter/IntFormalParameter.h"

#include "FX/Niagara/v2/ParameterValue/IntParameterValue.h"

UIntFormalParameter* UIntFormalParameter::New(UObject* Outer, int DefaultValue)
{
	auto Param = NewObject<UIntFormalParameter>(Outer, StaticClass());
	Param->Default = UIntParameterValue::New(Param, DefaultValue);
	Param->Type = INTEGER;
	return Param;
}
