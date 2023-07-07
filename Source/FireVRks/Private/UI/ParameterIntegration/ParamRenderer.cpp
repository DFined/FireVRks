#include "UI/ParameterIntegration/ParameterBindingBlock.h"
#include "UI/ParameterIntegration/ParameterBindingList.h"
#include "UI/ParameterIntegration/ParameterRenderer.h"
#include "UI/ParameterIntegration/SingleParameterBindingWidget.h"
#include "UI/ParameterIntegration/SystemInstantiationBindingWidget.h"


ParameterBindingWidget* UParameterRenderer::RenderParam(UDFUIContainer* Container, ParameterValueContext* ValueContext, AbstractFormalParameter* Parameter)
{
	ParameterBindingWidget* PBW;
	switch (Parameter->GetType())
	{
		case DFType::COMPOUND_BLOCK_PARAMETER: PBW = DFUIUtil::AddUserWidget<UParameterBindingBlock>(Container); break;
		case DFType::LIST_BLOCK_PARAMETER: PBW = DFUIUtil::AddUserWidget<UParameterBindingList>(Container); break;
		case DFType::SYSTEM_INSTANTIATION_PARAMETER: PBW = DFUIUtil::AddUserWidget<USystemInstantiationBindingWidget>(Container); break;
		default: PBW = DFUIUtil::AddUserWidget<USingleParameterBindingWidget>(Container); 
	}
	
	PBW->Initialize(ValueContext, Parameter);
	return PBW;
}
