// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FX/Niagara/v2/System/EffectSystem.h"
#include "UObject/Object.h"
#include "DisplayArrayLaunchData.generated.h"


UCLASS()
class FIREVRKS_API UDisplayArrayLaunchData : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	UParameterValueContext* Context;
	
	
};
