#include "UI/ParameterIntegration/ParameterBindingBlock.h"
#include "UI/ParameterIntegration/ParameterRenderer.h"
#include "UI/ParameterIntegration/SingleParameterBindingWidget.h"


ParameterBindingWidget* UParameterRenderer::RenderParam(UDFUIContainer* Container, ParameterValueContext* ValueContext, AbstractFormalParameter* Parameter)
{
	ParameterBindingWidget* PBW;
	if (Parameter->GetType() == DFType::COMPOUND_BLOCK_PARAMETER)
	{
		PBW = DFUIUtil::AddUserWidget<UParameterBindingBlock>(Container);
	}
	else
	{
		PBW = DFUIUtil::AddUserWidget<USingleParameterBindingWidget>(Container);
	}
	PBW->Initialize(ValueContext, Parameter);
	return PBW;
}
