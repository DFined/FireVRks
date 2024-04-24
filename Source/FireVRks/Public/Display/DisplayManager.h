// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DisplayManager.generated.h"

class ULevelSaveData;
class UDisplayData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDisplayLoaded);


UCLASS()
class FIREVRKS_API UDisplayManager : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	UDisplayData* DisplayInEditing = nullptr;

	FOnDisplayLoaded OnDisplayLoaded;

public:
	static UDisplayManager* MakeInstance()
	{
		auto Instance = NewObject<UDisplayManager>(GetTransientPackage());
		Instance->AddToRoot();
		return Instance;
	}

	UDisplayData* GetDisplayInEditing();

	void SetDisplayInEditing(UDisplayData* bDisplayInEditing);

	UFUNCTION(BlueprintCallable)
	static UDisplayManager* GetInstance()
	{
		if (!SingleInstance.IsValid())
		{
			SingleInstance = NewObject<UDisplayManager>();
			SingleInstance->AddToRoot();
		}
		return SingleInstance.Get();
	}

	FOnDisplayLoaded& GetOnDisplayLoaded();

private:
	inline static TWeakObjectPtr<UDisplayManager> SingleInstance = nullptr;
};
