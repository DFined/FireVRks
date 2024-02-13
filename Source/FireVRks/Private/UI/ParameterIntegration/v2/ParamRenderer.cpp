#include "DFUI/DFUI.h"
#include "UI/ParameterIntegration/v2/BlockParameterBindingWidget.h"
#include "UI/ParameterIntegration/v2/ListParameterBindingWidget.h"
#include "UI/ParameterIntegration/v2/ParameterDrawType.h"
#include "UI/ParameterIntegration/v2/ParameterLineBindingWidget.h"
#include "UI/ParameterIntegration/v2/ParameterRenderer.h"
#include "UI/ParameterIntegration/v2/SystemInstantiationParameterBindingWidget.h"


UParameterBindingWidget* UParameterRenderer::RenderParam(
	UDFUIBase* Container, UParameterValueContext* ValueContext, UAbstractFormalParameter* Parameter, ParameterDrawType DrawType)
{
	UParameterBindingWidget* PBW;
	switch (Parameter->GetType())
	{
		case BLOCK: PBW = DFUI::AddWidget<UBlockParameterBindingWidget>(Container); break;
		case LIST: PBW = DFUI::AddWidget<UListParameterBindingWidget>(Container); break;
		case SYSTEM_INSTANTIATION: PBW = DFUI::AddWidget<USystemInstantiationParameterBindingWidget>(Container); break;
		default: PBW = DFUI::AddWidget<UParameterLineBindingWidget>(Container); 
	}
	
	PBW->Setup(Parameter, ValueContext, DrawType);
	return PBW;
}
