// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DFEvent.h"
#include "FX/Niagara/v2/FormalParameter/AbstractFormalParameter.h"
#include "UObject/Object.h"
#include "Util/DFU.h"
#include "DFParameterEvent.generated.h"

UCLASS()
class FIREVRKS_API UDFParameterEvent : public UDFEvent
{
	GENERATED_BODY()

	UPROPERTY()
	UAbstractFormalParameter* Parameter;

	EDFEventType Type;
public:
	virtual EDFEventType GetType() override;

	UAbstractFormalParameter* GetParameter() const
	{
		return Parameter;
	}

private:
	void SetType(EDFEventType bType)
	{
		this->Type = bType;
	}

	void SetParameter(UAbstractFormalParameter* bParameter)
	{
		this->Parameter = bParameter;
	}

public:
	DF_NEW2(UDFParameterEvent, UAbstractFormalParameter*, Parameter, EDFEventType, Type);
};
