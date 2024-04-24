// Fill out your copyright notice in the Description page of Project Settings.


#include "Display/DisplayData.h"

#include "Display/DisplayLaunchSegment.h"
#include "Util/DFJsonUtil.h"

TArray<UDisplayLaunchSegment*>& UDisplayData::GetLaunchSegments()
{
	return LaunchSegments;
}

UDisplayData* UDisplayData::FromJson(UObject* Outer, TSharedPtr<FJsonObject> JsonObject)
{
	auto Display = New(Outer);
	Display->SetDisplayName(JsonObject->GetStringField("Name"));
	Display->SetAuthor(JsonObject->GetStringField("Author"));
	Display->SetTrackPath(JsonObject->GetStringField("TrackPath"));
	for (auto SegmentJson : JsonObject->GetArrayField("LaunchSegments"))
	{
		Display->GetLaunchSegments().Add(UDisplayLaunchSegment::FromJson(Display, SegmentJson->AsObject()));
	}
	return Display;
}

UDisplayData* UDisplayData::New(UObject* Outer)
{
	auto Data = NewObject<UDisplayData>(Outer, StaticClass());
	Data->TrackPath = "";
	Data->LaunchSegments = TArray<UDisplayLaunchSegment*>();
	return Data;
}

TSharedPtr<FJsonObject> UDisplayData::ToJson()
{
	auto Obj = new FJsonObject();
	Obj->SetStringField("Name", DisplayName);
	Obj->SetStringField("Author", Author);
	Obj->SetStringField("TrackPath", TrackPath);

	DFJsonUtil::SetArrayField(Obj, "LaunchSegments", LaunchSegments);
	return MakeShareable(Obj);
}

void UDisplayData::SetAuthor(const FString& bAuthor)
{
	this->Author = bAuthor;
}

void UDisplayData::SetTrackPath(const FString& bTrackPath)
{
	this->TrackPath = bTrackPath;
}

FString& UDisplayData::GetDisplayName()
{
	return DisplayName;
}

void UDisplayData::SetDisplayName(const FString BDisplayName)
{
	this->DisplayName = BDisplayName;
}
