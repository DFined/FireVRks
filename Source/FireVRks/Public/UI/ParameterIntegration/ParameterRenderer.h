#pragma once
#include "UI/DFUIUtil.h"
#include "ParameterRenderer.generated.h"

UCLASS(Abstract)
class UParameterRenderer : public UObject
{
	GENERATED_BODY()

public:
	static ParameterBindingWidget* RenderParam(UDFUIContainer* Container, ParameterValueContext* ValueContext, AbstractFormalParameter* Parameter);
};

