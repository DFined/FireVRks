// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractParameterValue.h"
#include "World/Launcher/GenericLauncherArray.h"
#include "ArraySelectorParameterValue.generated.h"

UCLASS()
class FIREVRKS_API UArraySelectorParameterValue : public UAbstractParameterValue
{
	GENERATED_BODY()

	/**
	 * An unset array is valid and even unavoidable until at least one array has been created, so this can and will be null by default
	 */
	UPROPERTY()
	UGenericLauncherArray* Array;

public:
	static UArraySelectorParameterValue* New(UObject* Outer, UGenericLauncherArray* bArray);

	UGenericLauncherArray* Get();
};
