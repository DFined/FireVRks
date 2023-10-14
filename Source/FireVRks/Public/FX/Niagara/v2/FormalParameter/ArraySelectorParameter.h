// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbstractFormalParameter.h"
#include "ArraySelectorParameter.generated.h"

UCLASS()
class FIREVRKS_API UArraySelectorParameter : public UAbstractFormalParameter
{
	GENERATED_BODY()

public:

	static UArraySelectorParameter* New(UObject* Outer);
	static UArraySelectorParameter* New(UObject* Outer, bool Expanded);

};
