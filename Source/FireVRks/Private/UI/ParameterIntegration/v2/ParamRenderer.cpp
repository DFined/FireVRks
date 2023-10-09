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
		case BLOCK: PBW = DFUIUtil::AddUserWidget<UBlockParameterBindingWidget>(Container); break;
		case LIST: PBW = DFUIUtil::AddUserWidget<UListParameterBindingWidget>(Container); break;
		case SYSTEM_INSTANTIATION: PBW = DFUIUtil::AddUserWidget<USystemInstantiationParameterBindingWidget>(Container); break;
		default: PBW = DFUIUtil::AddUserWidget<UParameterLineBindingWidget>(Container); 
	}
	
	PBW->Setup(Parameter, ValueContext);
	return PBW;
}
