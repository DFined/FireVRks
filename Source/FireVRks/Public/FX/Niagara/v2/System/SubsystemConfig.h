// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SubsystemParameterBindings.h"
#include "UObject/Object.h"
#include "Util/DFId.h"
#include "Util/DFU.h"
#include "SubsystemConfig.generated.h"

UCLASS()
class FIREVRKS_API USubsystemConfig : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	FString DisplayName = "New subsystem";

	UPROPERTY()
	USubsystemParameterBindings* Bindings;
	
	UPROPERTY()
	UDFId* Id;

public:
	DF_NEW1(USubsystemConfig, UDFId*, Id)

	FString GetSubsystemName() const
	{
		return DisplayName;
	}

	void SetSubsystemName(const FString& bSubsystemName)
	{
		this->DisplayName = bSubsystemName;
	}

	UDFId* GetId() const
	{
		return Id;
	}

	void SetId(UDFId* bId)
	{
		this->Id = bId;
	}

	USubsystemParameterBindings* GetBindings() const
	{
		return Bindings;
	}

	DF_CHILD_MEMBER(USubsystemParameterBindings, Bindings)

	TSharedPtr<FJsonObject> ToJson()
	{
		auto Obj = new FJsonObject();
		Obj->SetStringField("Id", Id->GetId());
		Obj->SetStringField("DisplayName", DisplayName);
		Bindings->AddToJson(Obj);
		return MakeShareable(Obj);
	}

	static USubsystemConfig* FromJson(TSharedPtr<FJsonObject> Json, UObject* Outer)
	{
		auto Config = Instance(Outer, UDFId::Named(Outer, Json->GetStringField("Id")));
		Config->SetSubsystemName(Json->GetStringField("DisplayName"));
		Config->Bindings = USubsystemParameterBindings::GetFromJson(Json, Config); 
		return Config;
	}
};
