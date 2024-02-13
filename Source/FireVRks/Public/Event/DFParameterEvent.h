// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DFEvent.h"
#include "UObject/Object.h"
#include "Util/DFU.h"
#include "DFParameterEvent.generated.h"

class UAbstractFormalParameter;

UCLASS()
class FIREVRKS_API UDFParameterEvent : public UDFEvent
{
	GENERATED_BODY()

	UPROPERTY()
	UAbstractFormalParameter* Parameter;

	EDFEventType Type;
public:
	virtual EDFEventType GetType() override;

	UAbstractFormalParameter* GetParameter() const;

private:
	void SetType(EDFEventType bType);

	void SetParameter(UAbstractFormalParameter* bParameter);

public:
	DF_NEW2(UDFParameterEvent, UAbstractFormalParameter*, Parameter, EDFEventType, Type);
};
