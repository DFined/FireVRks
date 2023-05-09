#include "DFTesting.h"

#include "FX/Niagara/SystemSettings/InstanceParameter/MapParameterValueContext.h"
#include "FX/Niagara/SystemSettings/ParamSystem/DefaultParameterSystem.h"
#include "UI/ParameterIntegration/ParameterInputUI.h"
#include "UI/ParameterIntegration/ParameterRenderer.h"

UParameterInputUI* UDFTesting::MockParameters(UPanelWidget* Outer)
{
	auto ParamUI = DFUIUtil::AddUserWidget<UParameterInputUI>(Outer);
	auto MockValueContext = MapParameterValueContext();
	UDefaultParameterSystem::Initialize();
	ParamUI->AddParameters(UDefaultParameterSystem::GetParameters());
	ParamUI->Draw(&MockValueContext);
		
	return ParamUI;
}