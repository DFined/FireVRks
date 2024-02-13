// Fill out your copyright notice in the Description page of Project Settings.


#include "Event/DFParameterEvent.h"

EDFEventType UDFParameterEvent::GetType()
{
	return Type;
}

UAbstractFormalParameter* UDFParameterEvent::GetParameter() const
{
	return Parameter;
}

void UDFParameterEvent::SetType(EDFEventType bType)
{
	this->Type = bType;
}

void UDFParameterEvent::SetParameter(UAbstractFormalParameter* bParameter)
{
	this->Parameter = bParameter;
}
