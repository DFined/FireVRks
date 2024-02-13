// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PanelWidget.h"
#include "FormalParameter/ParameterType.h"
#include "System/SubsystemParameterBindings.h"
#include "UI/ParameterIntegration/v2/ParameterCreatorInput.h"
#include "Util/DFId.h"
#include "Util/DFStatics.h"
#include "ParamUtil.generated.h"

#define INT_VALUE UIntParameterValue, int
#define FLOAT_VALUE UFloatParameterValue, float
#define BOOL_VALUE UBoolParameterValue, bool
#define ENUM_VALUE UEnumParameterValue, EnumLikeValue*

class UAbstractFormalParameter;
class UParameterValueContext;
class UAbstractParameterValue;
class WidgetWithValue;

UCLASS()
class FIREVRKS_API UParamUtil : public UObject
{
	GENERATED_BODY()

	static TMap<FString, ParameterType> InitTypes()
	{
		auto Map = TMap<FString, ParameterType>();
		Map.Add("INTEGER", INTEGER);
		Map.Add("BOOLEAN", BOOLEAN);
		Map.Add("ENUM", ENUM);
		Map.Add("FLOAT", FLOAT);
		Map.Add("COLOR", COLOR);
		Map.Add("BLOCK", BLOCK);
		Map.Add("LIST", LIST);
		Map.Add("SYSTEM_INSTANTIATION", SYSTEM_INSTANTIATION);
		Map.Add("ARRAY_SELECTOR", ARRAY_SELECTOR);
		return Map;
	}
	
	static inline FString PARAMETER_NAMES[] = {
		"INTEGER",
		"BOOLEAN",
		"ENUM",
		"FLOAT",
		"COLOR",
		"BLOCK",
		"LIST",
		"SYSTEM_INSTANTIATION",
		"ARRAY_SELECTOR"
	};

	static inline TMap<FString, ParameterType> TypeNameMap = InitTypes();

	static inline ParameterType TYPES[] = {
		INTEGER,
		BOOLEAN,
		ENUM,
		FLOAT,
		COLOR,
		BLOCK,
		LIST,
		SYSTEM_INSTANTIATION,
		ARRAY_SELECTOR
	};


public:
	static WidgetWithValue* GetValueWidget(UUserWidget* Outer, ParameterType Type);

	template <class OuterType, typename InnerType>
	static InnerType GetTypedValue(UAbstractParameterValue* Value)
	{
		return Cast<OuterType>(Value)->Get();
	}

	template <class Type>
	static Type* Setup(FString Id, FString Name, bool Required, Type* Parameter)
	{
		Parameter->SetRequired(Required);
		Parameter->SetDisplayName(Name);
		Parameter->SetId(UDFId::Named(UDFStatics::ANCHOR, Id));
		return Parameter;
	}

	template <class Type>
	static Type* Setup(FString Name, bool Required, Type* Parameter)
	{
		return Setup(FGuid::NewGuid().ToString(), Name, Required, Parameter);
	}

	template <class Param, typename Value>
	static Param* Global(FString Name, bool Required, Value DefaultValue)
	{
		return Setup<Param>(Name, Required, Param::New(UDFStatics::ANCHOR, DefaultValue));
	}


	template <class Param>
	static Param* Global(FString Name, bool Required)
	{
		return Setup<Param>(Name, Required, Param::New(UDFStatics::ANCHOR));
	}

	static void WriteContainerToContext(UPanelWidget* Container, UParameterValueContext* Context);

	static FString Name(ParameterType Type)
	{
		return PARAMETER_NAMES[Type];
	}

	static ParameterType Type(int Ordinal)
	{
		return UParameterCreatorInput::INSTANTIABLE_TYPES[Ordinal];
	}

	static ParameterType TypeFromName(FString Name){
		return *TypeNameMap.Find(Name);
	}

	static UAbstractFormalParameter* NewParam(UObject* Outer, FString Name, bool Required, ParameterType Type);
	static UAbstractParameterValue* ValueFromJson(TSharedPtr<FJsonObject> Json, UObject* Outer);
};
