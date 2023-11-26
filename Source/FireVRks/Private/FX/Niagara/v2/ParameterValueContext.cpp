#include "FX/Niagara/v2/ParameterValueContext.h"

#include "FX/Niagara/v2/BindingParameterValueContext.h"
#include "FX/Niagara/v2/MapParameterValueContext.h"

UBindingParameterValueContext* UParameterValueContext::NewContextFrom(UParameterValueContext* Context)
{
	if (auto BindingContext = Cast<UBindingParameterValueContext*>(Context))
	{
		UBindingParameterValueContext*  ResContext = UBindingParameterValueContext::New(Context);
		auto Inner = UMapParameterValueContext::New(ResContext);

		ResContext->SetOuterContext(Inner);
	}
}
