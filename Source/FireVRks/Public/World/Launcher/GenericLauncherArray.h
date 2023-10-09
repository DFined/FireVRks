#pragma once
#include "GenericFireworkLauncher.h"
#include "GenericLauncherArray.generated.h"

UCLASS(BlueprintType, Blueprintable)
class FIREVRKS_API UGenericLauncherArray : public UObject
{
	GENERATED_BODY()
	FString ArrayName;
	UPROPERTY()
	TArray<AGenericFireworkLauncher*> Launchers;
public:
	UFUNCTION(BlueprintCallable)
	FString GetArrayName() const;

	void SetArrayName(const FString& NewArrayName);

	UFUNCTION(BlueprintCallable)
	void AddLauncher(AGenericFireworkLauncher* Launcher);

	UFUNCTION(BlueprintCallable)
	int GetSize();

	TArray<AGenericFireworkLauncher*>* GetLaunchers()
	{
		return &Launchers;
	}
};
