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
	inline static const char* BindingsFieldName = "Bindings";

	
	UPROPERTY()
	TMap<FDFId, UAbstractFormalParameter*> Bindings = TMap<FDFId, UAbstractFormalParameter*>();

	UPROPERTY()
	TMap<FDFId, UAbstractParameterValue*> ConstantValues = TMap<FDFId, UAbstractParameterValue*>();
	

public:	
	TMap<FDFId, UAbstractFormalParameter*>& GetBindings() 
	{
		return Bindings;
	}

	TMap<FDFId, UAbstractParameterValue*>& GetConstantValues() 
	{
		return ConstantValues;
	}

	DF_NEW(USubsystemParameterBindings);

	void AddToJson(FJsonObject* Obj);

	static USubsystemParameterBindings* GetFromJson(TSharedPtr<FJsonObject> Json, UObject* Outer, TMap<FDFId, UAbstractFormalParameter*>& Outers);
};
