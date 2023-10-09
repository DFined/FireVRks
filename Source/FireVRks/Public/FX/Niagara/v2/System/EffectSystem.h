// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParameterProvider.h"
#include "UObject/Object.h"
#include "EffectSystem.generated.h"

/**
 * 
 */
UCLASS()
class FIREVRKS_API UEffectSystem : public UObject, public ParameterProvider
{
	GENERATED_BODY()

	UPROPERTY()
	UDFId* Id;

public:
	UDFId* GetId() const
	{
		return Id;
	}

	void SetId(UDFId* fId)
	{
		this->Id = fId;
	}

	virtual void Initialize() PURE_VIRTUAL("Initialize",);
};
