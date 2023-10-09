// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "AbstractParameterValue.h"
#include "FX/Niagara/SystemSettings/Enums/EnumLikeValue.h"
#include "EnumParameterValue.generated.h"

UCLASS()
class FIREVRKS_API UEnumParameterValue : public UAbstractParameterValue
{
	GENERATED_BODY()
	
	EnumLikeValue* Value;

public:
	static UEnumParameterValue* New(UObject* Outer, EnumLikeValue* Value);

	EnumLikeValue* Get() const;
};
