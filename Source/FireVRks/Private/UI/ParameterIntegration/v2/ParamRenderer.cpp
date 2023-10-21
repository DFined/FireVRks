#include "UI/DFUIUtil.h"
#include "UI/ParameterIntegration/v2/BlockParameterBindingWidget.h"
#include "UI/ParameterIntegration/v2/ListParameterBindingWidget.h"
#include "UI/ParameterIntegration/v2/ParameterLineBindingWidget.h"
#include "UI/ParameterIntegration/v2/ParameterRenderer.h"
#include "UI/ParameterIntegration/v2/SystemInstantiationParameterBindingWidget.h"


UParameterBindingWidget* UParameterRenderer::RenderParam(UDFUIContainer* Container, UParameterValueContext* ValueContext, UAbstractFormalParameter* Parameter)
{
	UParameterBindingWidget* PBW;
	switch (Parameter->GetType())
	{
		case BLOCK: PBW = UDFUIUtil::AddUserWidget<UBlockParameterBindingWidget>(Container); break;
		case LIST: PBW = UDFUIUtil::AddUserWidget<UListParameterBindingWidget>(Container); break;
		case SYSTEM_INSTANTIATION: PBW = UDFUIUtil::AddUserWidget<USystemInstantiationParameterBindingWidget>(Container); break;
		default: PBW = UDFUIUtil::AddUserWidget<UParameterLineBindingWidget>(Container); 
	}
	
	PBW->Setup(Parameter, ValueContext);
	return PBW;
}
