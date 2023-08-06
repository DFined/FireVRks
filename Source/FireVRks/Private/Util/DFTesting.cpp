#include "Util/DFTesting.h"

#include "FX/Niagara/System/EffectSystemManager.h"
#include "FX/Niagara/SystemSettings/InstanceParameter/MapParameterValueContext.h"
#include "UI/ParameterIntegration/EffectParameterInputUI.h"
#include "UI/ParameterIntegration/ParameterRenderer.h"

UEffectParameterInputUI* UDFTesting::MockParameters(UPanelWidget* Outer)
{
	auto ParamUI = DFUIUtil::AddUserWidget<UEffectParameterInputUI>(Outer);
	auto MockValueContext = MapParameterValueContext(true);
	EffectSystemManager::Initialize();
	ParamUI->SetSystem(EffectSystemManager::DEFAULT_EFFECT);
	ParamUI->Draw(&MockValueContext);
		
	return ParamUI;
}