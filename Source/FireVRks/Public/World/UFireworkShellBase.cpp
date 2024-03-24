#include "UFireworkShellBase.h"

#include "NiagaraComponent.h"
#include "FX/Niagara/Scheduler/SystemSpawnData.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Util/DFStatics.h"

AFireworkShellBase::AFireworkShellBase(): System(nullptr), Context(nullptr), Component(nullptr), Lifetime(0)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.SetTickFunctionEnable(true);
}

void AFireworkShellBase::Spawn()
{
	auto Velocity = Component->Velocity;
	Velocity.Normalize(0.05);
	System->SpawnSystem(USystemSpawnData::New(this, Context, this->GetActorLocation(), Velocity));
}

void AFireworkShellBase::DestroyShell(UNiagaraComponent* PSystem)
{
	this->Destroy();
}


void AFireworkShellBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	Lifetime -= DeltaSeconds;
	if (Lifetime <= 0 && !IsSpawned)
	{
		Spawn();
		IsSpawned = true;
		Emitter->Deactivate();
	}
}

void AFireworkShellBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	auto LocalTransform = FTransform(FRotator(), FVector(), FVector(0.05,0.05,0.05));
	auto Sphere = Cast<UStaticMeshComponent>(AddComponentByClass(UStaticMeshComponent::StaticClass(), false, LocalTransform, false));
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Sphere->SetStaticMesh(UDFStatics::SPHERE_MESH);

	Emitter = Cast<UNiagaraComponent>(AddComponentByClass(UNiagaraComponent::StaticClass(), false, LocalTransform, false));
	Emitter->SetAsset(UDFStatics::TRAIL_SYSTEM);
	Emitter->Activate(true);
	Emitter->OnSystemFinished.AddUniqueDynamic(this, &AFireworkShellBase::DestroyShell);
}

AFireworkShellBase* AFireworkShellBase::MakeShell(UObject* ContextObject, FVector* Location, FRotator* Rotation, ULaunchSettings* Settings)
{
	auto World = GEngine->GetWorldFromContextObject(ContextObject, EGetWorldErrorMode::ReturnNull);

	auto Shell = Cast<AFireworkShellBase>(World->SpawnActor(StaticClass(), Location, Rotation));
	Shell->System = Settings->GetSystem();
	Shell->Context = Settings->GetContext();
	Shell->Lifetime = Settings->GetShellLifetime();
	Shell->SetActorLocation(*Location);
	Shell->Component = Cast<UProjectileMovementComponent>(
		Shell->AddComponentByClass(UProjectileMovementComponent::StaticClass(), false, FTransform(), false)
	);
	Shell->Component->SetVelocityInLocalSpace(Rotation->RotateVector(FVector(1,0,0)) * Settings->GetShellVelocity());
	Shell->Settings = Settings;
	return Shell;
}

void AFireworkShellBase::BeginDestroy()
{
	Super::BeginDestroy();
}
