// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PanelWidget.h"
#include "UI/ParameterIntegration/v2/WidgetWithValue.h"
#include "UObject/Object.h"
#include "Util/DFStatics.h"
#include "ParamUtil.generated.h"

#define INT_VALUE UIntParameterValue, int
#define FLOAT_VALUE UFloatParameterValue, float
#define BOOL_VALUE UBoolParameterValue, bool
#define ENUM_VALUE UEnumParameterValue, EnumLikeValue*

UCLASS()
class FIREVRKS_API UParamUtil : public UObject
{
	GENERATED_BODY()

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
	static WidgetWithValue* GetValueWidget(UUserWidget* Outer, UAbstractParameterValue* Value, ParameterType Type);

	template <class OuterType, typename InnerType>
	static InnerType GetTypedValue(UAbstractParameterValue* Value);

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
		return TYPES[Ordinal];
	}

	static UAbstractFormalParameter* NewParam(UObject* Outer, FString Name, bool Required, ParameterType Type);
};
