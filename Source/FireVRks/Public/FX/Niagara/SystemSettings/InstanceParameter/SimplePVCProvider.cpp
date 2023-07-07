#include "SimplePVCProvider.h"

ParameterValueContext* USimplePVCProvider::Get()
{
	return Context;
}

UParameterValueContextProvider* USimplePVCProvider::Of(ParameterValueContext* Context, UObject* Outer)
{
	auto Prov = NewObject<USimplePVCProvider>(Outer);
	Prov->SetContext(Context);
	return Prov;
}
