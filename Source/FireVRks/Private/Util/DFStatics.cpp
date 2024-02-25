#include "Util/DFStatics.h"

#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "FX/Niagara/Scheduler/EffectSpawnCoordinator.h"
#include "FX/Niagara/v2/System/EffectSystemManager.h"
#include "UI/Icons.h"
#include "World/Launcher/ArrayLaunchPattern.h"
#include "World/Launcher/LauncherManager.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "Slate/SlateBrushAsset.h"

UDFAnchor* const UDFStatics::ANCHOR = UDFAnchor::Instance();

UIcons* const UDFStatics::ICONS = UIcons::StaticInstance();
UDFId* const UDFStatics::DEFAULT_SYSTEM_ID = UDFId::Named(ANCHOR, "{BUILTIN}-DEFAULT_SYSTEM");
UStaticMesh* const UDFStatics::SPHERE_MESH = LoadObject<UStaticMesh>(ANCHOR, TEXT("/Engine/EngineMeshes/Sphere.Sphere"));
UNiagaraSystem* const UDFStatics::DEFAULT_SYSTEM = LoadObject<UNiagaraSystem>(ANCHOR, TEXT("/Game/FireVRks/Effects/Systems/FibonacciSphere.FibonacciSphere"));
UNiagaraSystem* const UDFStatics::TRAIL_SYSTEM = LoadObject<UNiagaraSystem>(ANCHOR, TEXT("/Game/FireVRks/Effects/Systems/Trail.Trail"));
USlateBrushAsset* const UDFStatics::EFFECT_TESTING_SLATE_BRUSH = LoadObject<USlateBrushAsset>(ANCHOR, TEXT("/Game/FireVRks/UI/EffectTestBrush.EffectTestBrush"));
ULauncherManager* const UDFStatics::LAUNCHER_MANAGER = ULauncherManager::MakeInstance();
UArrayLaunchPattern* const UDFStatics::ARRAY_LAUNCH_PATTERN = UArrayLaunchPattern::MakeInstance();
UEffectSpawnCoordinator* const UDFStatics::EFFECT_SPAWN_COORDINATOR = UEffectSpawnCoordinator::New();
AActor* UDFStatics::Player = nullptr;
UCameraComponent* UDFStatics::PlayerCamera = nullptr;

ULauncherManager* UDFStatics::GetLauncherManager()
{
	return LAUNCHER_MANAGER;
}

UArrayLaunchPattern* UDFStatics::GetArrayLaunchPattern()
{
	return ARRAY_LAUNCH_PATTERN;
}



void UDFStatics::Reset()
{
	LAUNCHER_MANAGER->Reset();
	EFFECT_SPAWN_COORDINATOR->Reset();
}

TArray<FString> UDFStatics::GetFiles(FString FileTypes)
{
	const void* ParentWindowWindowHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);

	
	TArray<FString> OutFilenames = TArray<FString>();
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (DesktopPlatform)
	{
		DesktopPlatform->OpenFileDialog(
			ParentWindowWindowHandle,
			"Select file to play",
			TEXT(""),
			TEXT(""),
			FileTypes,
			EFileDialogFlags::None,
			OutFilenames
		);
	}
	return OutFilenames;
}

UEffectSpawnCoordinator* UDFStatics::GetCoordinator()
{
	return EFFECT_SPAWN_COORDINATOR;
}

AActor* UDFStatics::GetPlayer()
{
	return Player;
}

void UDFStatics::SetPlayer(AActor* bPlayer)
{
	Player = bPlayer;
}

void UDFStatics::SetPlayerCamera(UCameraComponent* bCamera)
{
	PlayerCamera = bCamera;
}

UCameraComponent* UDFStatics::GetPlayerCamera()
{
	return PlayerCamera;
}
