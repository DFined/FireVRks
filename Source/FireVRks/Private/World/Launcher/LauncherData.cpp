// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Launcher/LauncherData.h"

#include "Util/DFJsonUtil.h"
#include "World/Launcher/LauncherManager.h"

TSharedPtr<FJsonObject> ULauncherData::ToJson() const
{
	auto Obj = new FJsonObject();
	DFJsonUtil::WriteVectorToJson(Obj, "Position", Location);
	DFJsonUtil::WriteRotatorToJson(Obj, "Rotation", Rotation);
	return MakeShareable(Obj);
}


void ULauncherData::FromJson(TSharedPtr<FJsonObject> Json, FString ArrayName, UObject* WCO)
{
	auto Loc = DFJsonUtil::ReadVectorFromJson(Json, "Position");
	auto Rot = DFJsonUtil::ReadRotatorFromJson(Json, "Rotation");
	ULauncherManager::GetInstance()->AddLauncher(Loc, Rot, WCO, ArrayName);
}

AGenericFireworkLauncher* ULauncherData::GetActor()
{
	return Launcher;
}

void ULauncherData::Materialize(UWorld* World)
{
	if (!Launcher)
	{
		Launcher = Cast<AGenericFireworkLauncher>(World->SpawnActor(AGenericFireworkLauncher::StaticClass(), &Location, &Rotation));
	}
}

FVector& ULauncherData::GetLocation()
{
	return Location;
}

void ULauncherData::SetLocation(const FVector& bLocation)
{
	this->Location = bLocation;
}

FRotator& ULauncherData::GetRotation()
{
	return Rotation;
}

void ULauncherData::SetRotation(const FRotator& bRotation)
{
	this->Rotation = bRotation;
}
