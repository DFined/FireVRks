#include "FX/Niagara/v2/FormalParameter/BlockFormalParameter.h"

#include "FX/Niagara/v2/ParameterValue/BlockParameterValue.h"

void UBlockFormalParameter::Add(UAbstractFormalParameter* Child)
{
	ChildParameters.Add(Child);
}

UBlockFormalParameter* UBlockFormalParameter::New(UObject* Outer, bool Expanded)
{
	auto Param = NewObject<UBlockFormalParameter>(Outer, StaticClass());
	Param->ChildParameters = TArray<UAbstractFormalParameter*>(); 
	Param->Default = UBlockParameterValue::New(Param, Expanded, false);
	Param->Type = BLOCK;
	return Param;
}
