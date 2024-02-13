// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Util/DFId.h"
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
	TArray<USubsystemConfig*> SubsystemConfig = TArray<USubsystemConfig*>();

	UPROPERTY()
	TMap<UDFId*, UAbstractFormalParameter*> OuterParameters = TMap<UDFId*, UAbstractFormalParameter*>();

	UPROPERTY()
	TArray<UDFId*> ParameterOrder;

	UPROPERTY()
	UIcon* Icon;

	FCustomSystemEvent EventCallback;

public:
	virtual void SpawnSystem(USystemSpawnData* Data) override;

	TArray<USubsystemConfig*>& GetSubsystemConfig();

	virtual TMap<UDFId*, UAbstractFormalParameter*>* GetOuterParameters() override;
	virtual void GetOuterParametersInOrder(TArray<UAbstractFormalParameter*>& Result) override;

	DF_NEW_INIT(UCustomEffectSystem, Initialize);

	virtual void Initialize() override;

	FCustomSystemEvent& GetEventCallback();

	void DeleteParameter(UAbstractFormalParameter* Parameter);

	void FindAvailableOuters(ParameterType Type, TArray<UAbstractFormalParameter*>& Results);

	void NewParameter(UAbstractFormalParameter* Parameter);

	void MoveOuterParameterUp(UDFId* bId);

	void MoveOuterParameterDown(UDFId* bId);

	virtual UIcon* GetIcon() override;
	void SetIcon(UIcon* Icon);


	TSharedPtr<FJsonObject> ToJson();

	static UCustomEffectSystem* FromJson(TSharedPtr<FJsonObject> Json, UObject* Parent);
};
