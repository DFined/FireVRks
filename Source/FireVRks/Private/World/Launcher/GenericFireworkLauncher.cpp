#include "World/Launcher/GenericFireworkLauncher.h"

#include "Util/DFStatics.h"
#include "World/UFireworkShellBase.h"
#include "World/Launcher/LauncherManager.h"

void AGenericFireworkLauncher::OpenUI()
{
	DoOpenUI();
}

AGenericFireworkLauncher::AGenericFireworkLauncher()
{
	UDFStatics::LAUNCHER_MANAGER->AddLauncher(this);
}

void AGenericFireworkLauncher::Fire(ULaunchSettings* LaunchSettings)
{
	FVector Vector = this->GetActorLocation();
	FRotator Rotator = this->GetActorRotation();
	AFireworkShellBase::MakeShell(
		this,
		&Vector,
		&Rotator,
		LaunchSettings
	);
}

void AGenericFireworkLauncher::DoOpenUI_Implementation()
{
	
}
