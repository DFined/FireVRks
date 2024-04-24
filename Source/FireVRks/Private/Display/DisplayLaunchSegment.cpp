// Fill out your copyright notice in the Description page of Project Settings.


#include "Display/DisplayLaunchSegment.h"

#include "FX/Niagara/v2/BindingParameterValueContext.h"
#include "FX/Niagara/v2/MapParameterValueContext.h"

TArray<UParameterValueContext*>* UDisplayLaunchSegment::GetLaunchSettings()
{
	return &LaunchSettings;
}

TSharedPtr<FJsonObject> UDisplayLaunchSegment::ToJson()
{
	auto Obj = new FJsonObject();
	Obj->SetNumberField("Time", Time);

	auto Settings = TArray<TSharedPtr<FJsonValue>>();
	for(auto Context : LaunchSettings)
	{
		Settings.Add(MakeShareable(new FJsonValueObject(Context->ToJson())));
	}
	Obj->SetArrayField("LaunchSettings", Settings);
	
	return MakeShareable(Obj);
}

UDisplayLaunchSegment* UDisplayLaunchSegment::FromJson(UObject* Outer, TSharedPtr<FJsonObject> Json)
{
	auto Segment = New(Outer);
	Segment->SetTime(Json->GetNumberField("Time"));
	Segment->LaunchSettings.Empty();
	for (auto ContextJson : Json->GetArrayField("LaunchSettings"))
	{
		Segment->LaunchSettings.Add(UMapParameterValueContext::FromJson(ContextJson->AsObject(), Segment));
	}
	return Segment;
}

UDisplayLaunchSegment* UDisplayLaunchSegment::New(UObject* Outer)
{
	auto Segment = NewObject<UDisplayLaunchSegment>(Outer, StaticClass());
	Segment->LaunchSettings = TArray<UParameterValueContext*>();
	return Segment;
}
