#include "FX/Niagara/v2/FormalParameter/BoolFormalParameter.h"

#include "FX/Niagara/v2/ParameterValue/BoolParameterValue.h"

UBoolFormalParameter* UBoolFormalParameter::New(UObject* Outer, bool Default)
{
	auto Param = NewObject<UBoolFormalParameter>(Outer, StaticClass());
	Param->Default = UBoolParameterValue::New(Param, Default);
	Param->Type = BOOLEAN;
	return Param;
}
