// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/Niagara/v2/System/CustomEffectSystem.h"

#include "FX/Niagara/Scheduler/SystemSpawnData.h"
#include "FX/Niagara/v2/BindingParameterValueContext.h"
#include "FX/Niagara/v2/MapParameterValueContext.h"
#include "FX/Niagara/v2/System/SubsystemConfig.h"
#include "Util/DFStatics.h"

void UCustomEffectSystem::SpawnSystem(USystemSpawnData* Data)
{
	TArray<UDFId*> SystemIds = TArray<UDFId*>();
	SubsystemConfig.GetKeys(SystemIds);

	for (UDFId* SystemId : SystemIds)
	{
		auto Configs = *SubsystemConfig.Find(SystemId);

		UBindingParameterValueContext* Context = UBindingParameterValueContext::New(this);
		Context->SetOuterContext(Data->GetContext());
		Context->SetBindings(Configs->GetBindings());

		auto SubData = USystemSpawnData::New(
			Data->GetWorldObject(),
			Context,
			Data->GetLocation(),
			Data->GetUpwardVector()
		);
		SubData->AddToRoot();
		UDFStatics::EFFECT_SYSTEM_MANAGER->Get(Configs->GetId())->SpawnSystem(SubData);
		SubData->RemoveFromRoot();
	}
}

TMap<UDFId*, USubsystemConfig*>& UCustomEffectSystem::GetSubsystemConfig()
{
	return SubsystemConfig;
}

TMap<UDFId*, UAbstractFormalParameter*>* UCustomEffectSystem::GetOuterParameters()
{
	return &OuterParameters;
}

void UCustomEffectSystem::GetOuterParametersInOrder(TArray<UAbstractFormalParameter*>& Result)
{
	for (UDFId* bId : ParameterOrder)
	{
		Result.Add(*OuterParameters.Find(bId));
	}
}

FCustomSystemEvent& UCustomEffectSystem::GetEventCallback()
{
	return EventCallback;
}

void UCustomEffectSystem::DeleteParameter(UAbstractFormalParameter* Parameter)
{
	this->OuterParameters.Remove(Parameter->GetId());
	this->ParameterOrder.Remove(Parameter->GetId());
	EventCallback.Broadcast(UDFParameterEvent::Instance(this, Parameter, CUSTOM_SYSTEM_PARAMETER_DELETED));
}

void UCustomEffectSystem::FindAvailableOuters(ParameterType Type, TArray<UAbstractFormalParameter*>& Results)
{
	GET_MAP_VALUES(ParamsRes, UAbstractFormalParameter*, OuterParameters);
	for (UAbstractFormalParameter* Param : ParamsRes)
	{
		if (Param->GetType() == Type)
		{
			Results.Add(Param);
		}
	}
}

void UCustomEffectSystem::NewParameter(UAbstractFormalParameter* Parameter)
{
	OuterParameters.Add(Parameter->GetId(), Parameter);
	ParameterOrder.Add(Parameter->GetId());
	EventCallback.Broadcast(UDFParameterEvent::Instance(this, Parameter, CUSTOM_SYSTEM_PARAMETER_CREATED));
}
