// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/Niagara/v2/System/CustomEffectSystem.h"

#include "FX/Niagara/Scheduler/SystemSpawnData.h"
#include "FX/Niagara/v2/MapParameterValueContext.h"
#include "Util/DFStatics.h"

void UCustomEffectSystem::SpawnSystem(USystemSpawnData* Data)
{
	TArray<UDFId*> SystemIds = TArray<UDFId*>();
	SubsystemConfig.GetKeys(SystemIds);
	
	for (UDFId* SystemId : SystemIds)
	{
		UMapParameterValueContext* Context = UMapParameterValueContext::New(this);
		auto Bindings = *SubsystemConfig.Find(SystemId);
		
		for(UAbstractFormalParameter* Parameter: OuterParameters){
			Context->SetValue(*Bindings->GetBindings().Find(Parameter->GetId()), Data->GetContext()->Get(Parameter));
		}
		
		TArray<UDFId*> ConstantsIds = TArray<UDFId*>();
		Bindings->GetConstantValues().GetKeys(ConstantsIds);
		for(UDFId* ConstantId : ConstantsIds)
		{
			Context->SetValue(ConstantId, *Bindings->GetConstantValues().Find(ConstantId));
		}
		UDFStatics::EFFECT_SYSTEM_MANAGER->Get(SystemId)->SpawnSystem(Data);
	}
}
