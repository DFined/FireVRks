#include "FX/Niagara/v2/ParameterValueContext.h"

#include "FX/Niagara/v2/BindingParameterValueContext.h"
#include "FX/Niagara/v2/MapParameterValueContext.h"

UParameterValueContext* UParameterValueContext::FromJson(TSharedPtr<FJsonObject> Json, UObject* Outer, TMap<FDFId, UAbstractFormalParameter*> Outers)
{
	if (Json->HasField("ContextType"))
	{
		return UBindingParameterValueContext::FromJson(Json, Outer, Outers);
	}
	return UMapParameterValueContext::FromJson(Json, Outer);
}

UBindingParameterValueContext* UParameterValueContext::NewContextFrom(UParameterValueContext* Context)
{
	UBindingParameterValueContext* ResContext = UBindingParameterValueContext::New(Context);
	auto Inner = UMapParameterValueContext::Instance(ResContext);
	ResContext->SetOuterContext(Inner);
	return ResContext;
}
