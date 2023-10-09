#pragma once
#include "ParameterBindingWidget.h"
#include "ParameterRenderer.generated.h"

UCLASS(Abstract)
class FIREVRKS_API UParameterRenderer : public UObject
{
	GENERATED_BODY()

public:
	static UParameterBindingWidget* RenderParam(UDFUIContainer* Container, UParameterValueContext* ValueContext, UAbstractFormalParameter* Parameter);
};

