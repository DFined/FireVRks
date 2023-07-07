#include "FX/Niagara/SystemSettings/FormalParameter/SystemInstantiationFormalParameter.h"

#include "FX/Niagara/System/EffectSystemManager.h"
#include "FX/Niagara/SystemSettings/InstanceParameter/MapParameterValueContext.h"
#include "FX/Niagara/SystemSettings/ParameterValues/SystemInstantiationParameterValue.h"

AbstractParameterValue* SystemInstantiationFormalParameter::GetDefault()
{
	return new SystemInstantiationParameterValue(EffectSystemManager::DEFAULT_EFFECT, new MapParameterValueContext(false), false);
}
