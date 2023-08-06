#include "DFStatics.h"

#include "World/Launcher/LauncherManager.h"

UStaticMesh* const UDFStatics::SPHERE_MESH = LoadObject<UStaticMesh>(GetTransientPackage(), TEXT("/Engine/EngineMeshes/Sphere.Sphere"));
UNiagaraSystem* const UDFStatics::DEFAULT_SYSTEM = LoadObject<UNiagaraSystem>(GetTransientPackage(), TEXT("/Game/FireVRks/Effects/Systems/FibonacciSphere.FibonacciSphere"));
UNiagaraSystem* const UDFStatics::TRAIL_SYSTEM = LoadObject<UNiagaraSystem>(GetTransientPackage(), TEXT("/Game/FireVRks/Effects/Systems/Trail.Trail"));
UEffectSystemScheduler* const UDFStatics::EFFECT_SYSTEM_SCHEDULER = UEffectSystemScheduler::MakeInstance();
ULauncherManager* const UDFStatics::LAUNCHER_MANAGER = ULauncherManager::MakeInstance();

UEffectSystemScheduler* UDFStatics::GetEffectSystemScheduler()
{
	return EFFECT_SYSTEM_SCHEDULER;
}

ULauncherManager* UDFStatics::GetLauncherManager()
{
	return LAUNCHER_MANAGER;
}

void UDFStatics::Reset()
{
	LAUNCHER_MANAGER->Reset();
}
