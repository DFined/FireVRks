// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FX/Niagara/v2/FormalParameter/AbstractFormalParameter.h"
#include "FX/Niagara/v2/ParameterValue/AbstractParameterValue.h"
#include "UObject/Object.h"
#include "Util/DFId.h"
#include "Util/DFU.h"
#include "SubsystemParameterBindings.generated.h"

/**
 * Outer to inner parameter bindings for a subsystem instance
 */
UCLASS()
class FIREVRKS_API USubsystemParameterBindings : public UObject
{
	GENERATED_BODY()
	
	inline static const char* ConstantsFieldName = "ConstantValues";
	inline static const char* SubsystemsFieldName = "Bindings";

	
	UPROPERTY()
	TMap<UDFId*, UAbstractFormalParameter*> Bindings = TMap<UDFId*, UAbstractFormalParameter*>();

	UPROPERTY()
	TMap<UDFId*, UAbstractParameterValue*> ConstantValues = TMap<UDFId*, UAbstractParameterValue*>();
	

public:	
	TMap<UDFId*, UAbstractFormalParameter*>& GetBindings() 
	{
		return Bindings;
	}

	TMap<UDFId*, UAbstractParameterValue*>& GetConstantValues() 
	{
		return ConstantValues;
	}

	DF_NEW(USubsystemParameterBindings);

	void AddToJson(FJsonObject* Obj);

	static USubsystemParameterBindings* GetFromJson(TSharedPtr<FJsonObject> Json, UObject* Outer);
};
