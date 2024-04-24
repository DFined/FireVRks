#pragma once
#include "GenericLauncherArray.generated.h"

class ULauncherData;

UCLASS(BlueprintType, Blueprintable)
class FIREVRKS_API UGenericLauncherArray : public UObject
{
	GENERATED_BODY()
	FString ArrayName;
	UPROPERTY()
	TArray<ULauncherData*> Launchers;
public:
	UFUNCTION(BlueprintCallable)
	FString GetArrayName() const;

	void SetArrayName(const FString& NewArrayName);

	UFUNCTION(BlueprintCallable)
	void AddLauncher(ULauncherData* Launcher);

	UFUNCTION(BlueprintCallable)
	int GetSize();

	TArray<ULauncherData*>& GetLaunchers()
	{
		return Launchers;
	}

	TSharedPtr<FJsonObject> ToJson();

	static UGenericLauncherArray* FromJson(TSharedPtr<FJsonObject> Json, UObject* WCO);
};
