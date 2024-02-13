// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractParameterValue.h"
#include "BlockParameterValue.generated.h"

UCLASS()
class FIREVRKS_API UBlockParameterValue : public UAbstractParameterValue
{
	GENERATED_BODY()
	bool Expanded;
	bool OverridesExpanded;
	
public:
	bool IsExpanded() const
	{
		return Expanded;
	}

	bool IsOverridesExpanded() const
	{
		return OverridesExpanded;
	}

	static bool ValueFromJson(TSharedPtr<FJsonObject> Json);

	static UBlockParameterValue* New(UObject* Outer, bool Expanded, bool OverridesExpanded);

	virtual TSharedPtr<FJsonObject> ToJson() override;

	virtual UAbstractParameterValue* Clone(UAbstractFormalParameter* Param) override;
};
