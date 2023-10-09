// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractFormalParameter.h"
#include "ListFormalParameter.generated.h"

/**
 * 
 */
UCLASS()
class FIREVRKS_API UListFormalParameter : public UAbstractFormalParameter
{
	GENERATED_BODY()

	UPROPERTY()
	UAbstractFormalParameter* ChildType;

public:
	UAbstractFormalParameter* GetChildType() const
	{
		return ChildType;
	}
	
	static UListFormalParameter* New(UObject* Outer, UAbstractFormalParameter* ChildType);
};
