#pragma once
#include "DFAnchor.h"
#include "DFStatics.generated.h"

class UEffectSystem;
class UIcons;
class UFileHelper;
class UCameraComponent;
class UEffectSpawnCoordinator;
class UEffectSystemManager;
class ULauncherManager;
class USlateBrushAsset;
class UNiagaraSystem;
struct FDFId;
class UArrayLaunchPattern;

UCLASS()
class FIREVRKS_API UDFStatics : public UObject
{
	GENERATED_BODY()

public:
	static UDFAnchor* const ANCHOR;

	static FDFId const DEFAULT_SYSTEM_ID;
	static UStaticMesh* const SPHERE_MESH;
	static UNiagaraSystem* const DEFAULT_SYSTEM;
	static UNiagaraSystem* const TRAIL_SYSTEM;
	static USlateBrushAsset* const EFFECT_TESTING_SLATE_BRUSH;
	static ULauncherManager* const LAUNCHER_MANAGER;
	static UArrayLaunchPattern* const ARRAY_LAUNCH_PATTERN;
	static UEffectSpawnCoordinator* const EFFECT_SPAWN_COORDINATOR;
	static AActor* Player;
	static UCameraComponent* PlayerCamera;
	static UIcons* const ICONS;
	static UFileHelper* const FILE_HELPER;

	UFUNCTION(BlueprintCallable)
	static ULauncherManager* GetLauncherManager();

	UFUNCTION(BlueprintCallable)
	static UArrayLaunchPattern* GetArrayLaunchPattern();

	//Should be called on beginning play to clear globals
	UFUNCTION(BlueprintCallable)
	static void Reset();

	UFUNCTION(BlueprintCallable)
	static TArray<FString> GetFiles(FString FileTypes);

	UFUNCTION(BlueprintCallable)
	static UEffectSpawnCoordinator* GetCoordinator();

	template <class Type>
	static Type* New();

	static AActor* GetPlayer();

	UFUNCTION(BlueprintCallable)
	static void SetPlayer(AActor* bPlayer);

	UFUNCTION(BlueprintCallable)
	static void SetPlayerCamera(UCameraComponent* bCamera);

	UFUNCTION(BlueprintCallable)
	static UCameraComponent* GetPlayerCamera();
};

template <class Type>
Type* UDFStatics::New()
{
	auto Obj = NewObject<Type>(ANCHOR, Type::StaticClass());
	ANCHOR->Anchor(Obj);
	return Obj;
}
