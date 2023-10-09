// Fill out your copyright notice in the Description page of Project Settings.


#include "Display/DisplayLaunchSegment.h"

#include "FX/Niagara/v2/MapParameterValueContext.h"

TArray<UParameterValueContext*>* UDisplayLaunchSegment::GetLaunchSettings()
{
	return &LaunchSettings;
}

UDisplayLaunchSegment* UDisplayLaunchSegment::New(UObject* Outer)
{
	auto Segment = NewObject<UDisplayLaunchSegment>(Outer, StaticClass());
	Segment->LaunchSettings = TArray<UParameterValueContext*>();
	Segment->LaunchSettings.Add(NewObject<UMapParameterValueContext>(Segment, UMapParameterValueContext::StaticClass()));
	return Segment;
}
