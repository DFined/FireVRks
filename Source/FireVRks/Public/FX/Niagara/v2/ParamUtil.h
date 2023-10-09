// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PanelWidget.h"
#include "UI/ParameterIntegration/v2/WidgetWithValue.h"
#include "UObject/Object.h"
#include "Util/DFStatics.h"
#include "ParamUtil.generated.h"

#define INT_VALUE UIntParameterValue, int
#define FLOAT_VALUE UIntParameterValue, float
#define BOOL_VALUE UBoolParameterValue, bool
#define ENUM_VALUE UEnumParameterValue, EnumLikeValue*

UCLASS()
class FIREVRKS_API UParamUtil : public UObject
{
	GENERATED_BODY()

public:
	static WidgetWithValue* GetValueWidget(UUserWidget* Outer, UAbstractParameterValue* Value, ParameterType Type);

	template <class OuterType, typename InnerType>
	static InnerType GetTypedValue(UAbstractParameterValue* Value);

	template <class Type>
	static Type* Setup(FString Id, FString Name, bool Required, Type* Parameter);

	template <class Type>
	static Type* Setup(FString Name, bool Required, Type* Parameter);

	template<class Param, typename Value>
	static Param* Global(FString Name, bool Required, Value DefaultValue);

	static void WriteContainerToContext(UPanelWidget* Container, UParameterValueContext* Context);
};
