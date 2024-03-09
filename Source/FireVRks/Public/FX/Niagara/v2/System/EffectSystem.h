// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParameterProvider.h"
#include "DFUI/Icon.h"
#include "UObject/Object.h"
#include "EffectSystem.generated.h"

class USystemSpawnData;
class ULaunchSettings;

UCLASS()
class FIREVRKS_API UEffectSystem : public UObject, public ParameterProvider
{
	GENERATED_BODY()

	UPROPERTY()
	FDFId Id;

	FString DisplayName;

	FString Author;
	FString Description;

public:
	FDFId GetId() const
	{
		return Id;
	}

	void SetId(FDFId fId)
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
	virtual UIcon* GetIcon() PURE_VIRTUAL("GetIcon", return nullptr;);
	virtual void SpawnSystem(USystemSpawnData* Data) PURE_VIRTUAL("SpawnSystem",);
	virtual TMap<FDFId, UAbstractFormalParameter*>* GetOuterParameters() override PURE_VIRTUAL("GetOuterParameters", return nullptr;);
	virtual void GetOuterParametersInOrder(TArray<UAbstractFormalParameter*>& Result) override PURE_VIRTUAL("GetOuterParameters", ;);

	FString GetAuthor() const;
	void SetAuthor(const FString& Author);
	FString GetDescription() const;
	void SetDescription(const FString& Description);
};
