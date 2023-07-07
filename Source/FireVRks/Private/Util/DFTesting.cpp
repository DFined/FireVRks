#include "Util/DFTesting.h"

#include "FX/Niagara/System/EffectSystemManager.h"
#include "FX/Niagara/SystemSettings/InstanceParameter/MapParameterValueContext.h"
#include "UI/ParameterIntegration/ParameterInputUI.h"
#include "UI/ParameterIntegration/ParameterRenderer.h"

UParameterInputUI* UDFTesting::MockParameters(UPanelWidget* Outer)
{
	auto ParamUI = DFUIUtil::AddUserWidget<UParameterInputUI>(Outer);
	auto MockValueContext = MapParameterValueContext(true);
	EffectSystemManager::Initialize();
	ParamUI->SetSystem(EffectSystemManager::DEFAULT_EFFECT);
	ParamUI->Draw(&MockValueContext);
		
	return ParamUI;
}