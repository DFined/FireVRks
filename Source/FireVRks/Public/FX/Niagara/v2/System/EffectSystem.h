// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParameterProvider.h"
#include "UObject/Object.h"
#include "EffectSystem.generated.h"

class USystemSpawnData;
class ULaunchSettings;

UCLASS()
class FIREVRKS_API UEffectSystem : public UObject, public ParameterProvider
{
	GENERATED_BODY()

	UPROPERTY()
	UDFId* Id;

	FString DisplayName;

public:
	UDFId* GetId() const
	{
		return Id;
	}

	void SetId(UDFId* fId)
	{
		this->Id = fId;
	}

	FString GetDisplayName() const
	{
		return DisplayName;
	}

	void SetDisplayName(const FString& bDisplayName)
	{
		this->DisplayName = bDisplayName;
	}

	virtual void Initialize() PURE_VIRTUAL("Initialize",)
	virtual UTexture2D* GetIcon() PURE_VIRTUAL("GetIcon", return nullptr;);
	virtual void SpawnSystem(USystemSpawnData* Data) PURE_VIRTUAL("SpawnSystem",);
	virtual TMap<UDFId*, UAbstractFormalParameter*>* GetOuterParameters() override PURE_VIRTUAL("GetOuterParameters", return nullptr;);
	virtual void GetOuterParametersInOrder(TArray<UAbstractFormalParameter*>& Result) override PURE_VIRTUAL("GetOuterParameters", ;);
};
