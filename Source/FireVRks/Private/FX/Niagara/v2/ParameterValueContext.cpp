#include "FX/Niagara/v2/ParameterValueContext.h"

#include "FX/Niagara/v2/BindingParameterValueContext.h"
#include "FX/Niagara/v2/MapParameterValueContext.h"

UBindingParameterValueContext* UParameterValueContext::NewContextFrom(UParameterValueContext* Context)
{
	UBindingParameterValueContext* ResContext = UBindingParameterValueContext::New(Context);
	auto Inner = UMapParameterValueContext::Instance(ResContext);
	ResContext->SetOuterContext(Inner);
	return ResContext;
}
