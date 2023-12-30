// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectSystem.h"
#include "Event/DFParameterEvent.h"
#include "CustomEffectSystem.generated.h"

class USubsystemConfig;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCustomSystemEvent, UDFEvent*, Event);

/**
 * Class for storing user created effect systems
 */
UCLASS()
class FIREVRKS_API UCustomEffectSystem : public UEffectSystem
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<UDFId*, USubsystemConfig*> SubsystemConfig = TMap<UDFId*, USubsystemConfig*>();

	UPROPERTY()
	TMap<UDFId*, UAbstractFormalParameter*> OuterParameters = TMap<UDFId*, UAbstractFormalParameter*>();

	UPROPERTY()
	TArray<UDFId*> ParameterOrder;

	FCustomSystemEvent EventCallback;

public:
	virtual void SpawnSystem(USystemSpawnData* Data) override;

	TMap<UDFId*, USubsystemConfig*>& GetSubsystemConfig();

	virtual TMap<UDFId*, UAbstractFormalParameter*>* GetOuterParameters() override;
	virtual void GetOuterParametersInOrder(TArray<UAbstractFormalParameter*>& Result) override;

	DF_NEW(UCustomEffectSystem);


	FCustomSystemEvent& GetEventCallback();

	void DeleteParameter(UAbstractFormalParameter* Parameter);

	void FindAvailableOuters(ParameterType Type, TArray<UAbstractFormalParameter*>& Results);

	void NewParameter(UAbstractFormalParameter* Parameter);

	void MoveOuterParameterUp(UDFId* bId)
	{
		auto Num = ParameterOrder.Find(bId);
		if (Num > 0)
		{
			ParameterOrder.RemoveAt(Num);
			ParameterOrder.Insert(bId, Num - 1);
		}
	}

	void MoveOuterParameterDown(UDFId* bId)
	{
		auto Num = ParameterOrder.Find(bId);
		if (Num < ParameterOrder.Num() - 1)
		{
			ParameterOrder.RemoveAt(Num);
			ParameterOrder.Insert(bId, Num + 1);
		}
	}	
};
