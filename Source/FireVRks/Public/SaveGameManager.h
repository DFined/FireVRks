// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "UObject/Object.h"
#include "SaveGameManager.generated.h"

UCLASS()
class FIREVRKS_API USaveGameManager : public UObject
{
	GENERATED_BODY()

	inline static const FString DisplayFieldName = "DisplayInEditing";
	inline static const FString LaunchersFieldName = "LauncherArrays";

	TSharedPtr<FJsonObject> ToJson();

public:
	void DoLoadGame(FString Name, UObject* WCO);
	void DoSaveGame(FString Name);

	void SaveGame(UWorld* World);

	UFUNCTION()
	void ConfirmLoadGame(UWidget* Widget);
	void LoadGame(UObject* WCO);

	UFUNCTION()
	void ConfirmSave(UWidget* Widget);

	UFUNCTION()
	void CheckSaveSlot(UWidget* Widget);

	UFUNCTION(BlueprintCallable)
	static USaveGameManager* GetInstance()
	{
		if (!SingleInstance.IsValid())
		{
			SingleInstance = NewObject<USaveGameManager>();
			SingleInstance->AddToRoot();
		}
		return SingleInstance.Get();
	}

private:
	inline static TWeakObjectPtr<USaveGameManager> SingleInstance = nullptr;
};
