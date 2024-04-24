#include "World/Launcher/GenericFireworkLauncher.h"

#include "FX/Niagara/Scheduler/SystemSpawnData.h"
#include "Util/DFStatics.h"
#include "World/UFireworkShellBase.h"

void AGenericFireworkLauncher::OpenUI()
{
	DoOpenUI();
}

AGenericFireworkLauncher::AGenericFireworkLauncher()
{
	auto Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetStaticMesh(UDFStatics::SPHERE_MESH);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->RegisterComponent();
	Mesh->SetRelativeScale3D(FVector(0.2, 0.2, 0.2));
	SetRootComponent(Mesh);
}

void AGenericFireworkLauncher::Fire(ULaunchSettings* LaunchSettings)
{
	FVector Vector = this->GetActorLocation();
	auto LauncherUp = this->GetActorUpVector();
	auto UpVector = LauncherUp.RotateAngleAxis(LaunchSettings->GetDegressRoll(), this->GetActorRightVector());
	FRotator Rotator = UpVector.Rotation();
	//Bit of a hack, but honestly, you wont even get 100 fps in this sim ever, so lifetimes below .01s are meaningless anyway
	if (LaunchSettings->GetShellLifetime() > 0.01)
	{
		AFireworkShellBase::MakeShell(
			this,
			&Vector,
			&Rotator,
			LaunchSettings
		);
	}
	else
	{
		auto SpawnData = USystemSpawnData::New(this, LaunchSettings->GetContext(), Vector, UpVector);
		LaunchSettings->GetSystem()->SpawnSystem(SpawnData);
	}
}

void AGenericFireworkLauncher::DoOpenUI_Implementation()
{
}
