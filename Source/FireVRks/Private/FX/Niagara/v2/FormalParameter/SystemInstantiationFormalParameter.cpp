// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/Niagara/v2/FormalParameter/SystemInstantiationFormalParameter.h"

#include "FX/Niagara/v2/BindingParameterValueContext.h"

USystemInstantiationFormalParameter* USystemInstantiationFormalParameter::New(UObject* Outer, FDFId System)
{
	auto Param = NewObject<USystemInstantiationFormalParameter>(Outer, StaticClass());
	auto SubContext = UBindingParameterValueContext::New(Param);
	SubContext->SetOuterContext(UMapParameterValueContext::Instance(SubContext));
	SubContext->SetBindings(USubsystemParameterBindings::Instance(SubContext));
	Param->Default = USystemInstantiationParameterValue::New(
		Param, SubContext, System
	);
	Param->Type = SYSTEM_INSTANTIATION;
	return Param;
}
