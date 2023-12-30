// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DFEventType.h"
#include "UObject/Object.h"
#include "DFEvent.generated.h"

UCLASS()
class FIREVRKS_API UDFEvent : public UObject
{
	GENERATED_BODY()

public:
	virtual EDFEventType GetType() PURE_VIRTUAL("GetType", return NONE;);
};
