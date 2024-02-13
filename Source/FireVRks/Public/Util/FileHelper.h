// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DFU.h"
#include "UObject/Object.h"
#include "FileHelper.generated.h"

UCLASS()
class FIREVRKS_API UFileHelper : public UObject
{
	GENERATED_BODY()

	FString UserContentPath;
	FString IconsContentPath;
	FString SystemsContentPath;
public:
	DF_NEW_INIT(UFileHelper, Initialize)

	void Initialize()
	{
		AddToRoot();
		UserContentPath = FPaths::Combine(FPaths::ProjectContentDir(),"user_save");
		IconsContentPath = FPaths::Combine(UserContentPath, "icons");
		SystemsContentPath = FPaths::Combine(UserContentPath, "systems");
	}

	FString GetUserContentPath() const
	{
		return UserContentPath;
	}

	FString GetIconsContentPath() const
	{
		return IconsContentPath;
	}

	FString GetSystemsContentPath() const
	{
		return SystemsContentPath;
	}
};
