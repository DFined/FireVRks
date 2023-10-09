// Fill out your copyright notice in the Description page of Project Settings.


#include "Display/DisplayData.h"

TArray<UDisplayLaunchSegment*>* UDisplayData::GetLaunchSegments()
{
	return &LaunchSegments;
}

UDisplayData* UDisplayData::New(UObject* Outer)
{
	auto Data = NewObject<UDisplayData>(Outer, StaticClass());
	Data->TrackPath = "";
	Data->LaunchSegments = TArray<UDisplayLaunchSegment*>();
		
	Data->LaunchSegments.Add(UDisplayLaunchSegment::New(Data));
	return Data;
}
