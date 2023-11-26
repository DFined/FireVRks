#include "Util/DFStatics.h"

#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "World/Launcher/ArrayLaunchPattern.h"
#include "World/Launcher/LauncherManager.h"

UDFAnchor* const UDFStatics::ANCHOR = UDFAnchor::Instance();

UDFId* const UDFStatics::DEFAULT_SYSTEM_ID = UDFId::Named(ANCHOR, "{BUILTIN}-DEFAULT_SYSTEM");
UStaticMesh* const UDFStatics::SPHERE_MESH = LoadObject<UStaticMesh>(ANCHOR, TEXT("/Engine/EngineMeshes/Sphere.Sphere"));
UNiagaraSystem* const UDFStatics::DEFAULT_SYSTEM = LoadObject<UNiagaraSystem>(ANCHOR, TEXT("/Game/FireVRks/Effects/Systems/FibonacciSphere.FibonacciSphere"));
UNiagaraSystem* const UDFStatics::TRAIL_SYSTEM = LoadObject<UNiagaraSystem>(ANCHOR, TEXT("/Game/FireVRks/Effects/Systems/Trail.Trail"));
ULauncherManager* const UDFStatics::LAUNCHER_MANAGER = ULauncherManager::MakeInstance();
UArrayLaunchPattern* const UDFStatics::ARRAY_LAUNCH_PATTERN = UArrayLaunchPattern::MakeInstance();
UEffectSystemManager* const UDFStatics::EFFECT_SYSTEM_MANAGER = UEffectSystemManager::Instance();
UEffectSpawnCoordinator* const UDFStatics::EFFECT_SPAWN_COORDINATOR = UEffectSpawnCoordinator::New();
AActor* UDFStatics::Player = nullptr;

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
	EFFECT_SYSTEM_MANAGER->Initialize();
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

UEffectSystem* UDFStatics::GetDefaultEffectSystem()
{
	return EFFECT_SYSTEM_MANAGER->GetDefaultEffect();
}
