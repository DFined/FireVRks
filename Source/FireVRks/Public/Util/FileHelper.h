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
	FString DisplaysContentPath;

public:
	void Init()
	{
		AddToRoot();
		UserContentPath = FPaths::Combine(FPaths::ProjectContentDir(), "user_save");
		IconsContentPath = FPaths::Combine(UserContentPath, "icons");
		SystemsContentPath = FPaths::Combine(UserContentPath, "systems");
		DisplaysContentPath = FPaths::Combine(UserContentPath, "displays");
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

	FString& GetDisplaysContentPath();

	FString IconPath(FString& ChildPath)
	{
		return FPaths::Combine(GetIconsContentPath(), ChildPath);
	}

	FString SystemPath(FString& ChildPath)
	{
		return FPaths::Combine(GetSystemsContentPath(), ChildPath);
	}

	FString DisplayPath(FString& ChildPath)
	{
		return FPaths::Combine(GetDisplaysContentPath(), ChildPath);
	}

	void ListFilesInDir(FString Path, TArray<FString>& Result);

	UFUNCTION(BlueprintCallable)
	static UFileHelper* GetInstance()
	{
		if (!SingleInstance.IsValid())
		{
			SingleInstance = NewObject<UFileHelper>();
			SingleInstance->AddToRoot();
			SingleInstance->Init();
		}
		return SingleInstance.Get();
	}

private:
	inline static TWeakObjectPtr<UFileHelper> SingleInstance = nullptr;
};
