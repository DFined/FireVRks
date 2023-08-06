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

AFireworkShellBase* AGenericFireworkLauncher::Fire(USystemAndContext* SystemAndContext, float Delay, float Lifetime, float Velocity)
{
	FVector Vector =  this->GetActorLocation();
	FRotator Rotator = this->GetActorRotation();
	return AFireworkShellBase::MakeShell(
		this,
		&Vector,
		&Rotator,
		SystemAndContext->GetSystem(),
		SystemAndContext->GetContext(),
		Delay,
		Lifetime,
		Velocity
	);
}

void AGenericFireworkLauncher::DoOpenUI_Implementation()
{
}
