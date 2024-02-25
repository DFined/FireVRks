// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/Niagara/v2/System/CustomEffectSystem.h"

#include "FX/Niagara/Scheduler/SystemSpawnData.h"
#include "FX/Niagara/v2/BindingParameterValueContext.h"
#include "FX/Niagara/v2/MapParameterValueContext.h"
#include "FX/Niagara/v2/System/EffectSystemManager.h"
#include "FX/Niagara/v2/System/SubsystemConfig.h"
#include "UI/Icons.h"
#include "Util/DFJsonUtil.h"
#include "Util/DFStatics.h"

void UCustomEffectSystem::SpawnSystem(USystemSpawnData* Data)
{
	TArray<UDFId*> SystemIds = TArray<UDFId*>();

	for (auto Configs : SubsystemConfig)
	{
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
		UEffectSystemManager::GetInstance()->Get(Configs->GetId())->SpawnSystem(SubData);
		SubData->RemoveFromRoot();
	}
}

TArray<USubsystemConfig*>& UCustomEffectSystem::GetSubsystemConfig()
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

void UCustomEffectSystem::Initialize()
{
	this->SetDisplayName("New effect system");
	this->SetDescription("A new effect system");
	this->SetAuthor("Player");
	this->SetIcon(UDFStatics::ICONS->CUSTOM_EFFECT_ICON);
	this->SetId(UDFId::Random(this));
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

void UCustomEffectSystem::MoveOuterParameterUp(UDFId* bId)
{
	auto Num = ParameterOrder.Find(bId);
	if (Num > 0)
	{
		ParameterOrder.RemoveAt(Num);
		ParameterOrder.Insert(bId, Num - 1);
	}
}

void UCustomEffectSystem::MoveOuterParameterDown(UDFId* bId)
{
	auto Num = ParameterOrder.Find(bId);
	if (Num < ParameterOrder.Num() - 1)
	{
		ParameterOrder.RemoveAt(Num);
		ParameterOrder.Insert(bId, Num + 1);
	}
}

UIcon* UCustomEffectSystem::GetIcon()
{
	return Icon;
}

void UCustomEffectSystem::SetIcon(UIcon* bIcon)
{
	this->Icon = bIcon;
}

TSharedPtr<FJsonObject> UCustomEffectSystem::ToJson()
{
	auto Obj = new FJsonObject();
	Obj->SetStringField("Id", GetId()->GetId());
	Obj->SetStringField("DisplayName", GetDisplayName());
	Obj->SetStringField("Author", GetAuthor());
	Obj->SetStringField("Description", GetDescription());

	TArray<TSharedPtr<FJsonValue>> Outers = TArray<TSharedPtr<FJsonValue>>();
	for (auto bId : ParameterOrder)
	{
		auto Parameter = *OuterParameters.Find(bId);
		Outers.Add(MakeShareable(new FJsonValueObject(Parameter->ToJson())));
	}
	Obj->SetArrayField("OuterParameters", Outers);

	TArray<TSharedPtr<FJsonValue>> Subsystems = TArray<TSharedPtr<FJsonValue>>();
	for (auto Sub : SubsystemConfig)
	{
		Subsystems.Add(MakeShareable(new FJsonValueObject(Sub->ToJson())));
	}
	Obj->SetArrayField("Subsystems", Subsystems);
	return MakeShareable(Obj);
}

UCustomEffectSystem* UCustomEffectSystem::FromJson(TSharedPtr<FJsonObject> Json, UObject* Parent) 
{
	auto System = Instance(Parent);

	
	auto OuterParams = TArray<UAbstractFormalParameter*>();
	DFJsonUtil::GetArrayField<UAbstractFormalParameter>(Json, "OuterParameters", System, OuterParams);
	for(auto Param : OuterParams)
	{
		System->GetOuterParameters()->Add(Param->GetId(), Param);
	}

	DFJsonUtil::GetArrayField(Json, "Subsystems", System, System->GetSubsystemConfig());
	System->SetId(UDFId::Named(System,Json->GetStringField("Id")));
	System->SetDisplayName(Json->GetStringField("DisplayName"));
	System->SetDisplayName(Json->GetStringField("Author"));
	System->SetDisplayName(Json->GetStringField("Description"));
	
	return System;
}
