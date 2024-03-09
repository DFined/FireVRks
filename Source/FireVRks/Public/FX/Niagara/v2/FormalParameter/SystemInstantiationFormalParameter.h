// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractFormalParameter.h"
#include "FX/Niagara/v2/MapParameterValueContext.h"
#include "FX/Niagara/v2/ParameterValue/SystemInstantiationParameterValue.h"
#include "SystemInstantiationFormalParameter.generated.h"

UCLASS()
class FIREVRKS_API USystemInstantiationFormalParameter : public UAbstractFormalParameter
{
	GENERATED_BODY()

public:
	static USystemInstantiationFormalParameter* New(UObject* Outer, FDFId System);
};
