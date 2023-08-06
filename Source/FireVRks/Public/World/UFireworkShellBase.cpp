#include "UFireworkShellBase.h"

#include "NiagaraComponent.h"
#include "FX/Niagara/Scheduler/EffectSystemScheduler.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Util/DFStatics.h"

AFireworkShellBase::AFireworkShellBase()
{
	PrimaryActorTick.bCanEverTick=true;
	PrimaryActorTick.SetTickFunctionEnable(true);
}

void AFireworkShellBase::Spawn()
{
	UDFStatics::EFFECT_SYSTEM_SCHEDULER->SpawnNow(SpawnData);
}



void AFireworkShellBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	Lifetime -= DeltaSeconds;
	if (Lifetime <= 0)
	{
		Spawn();
		this->Destroy();
	}
}

void AFireworkShellBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	auto LocalTransform = FTransform(FRotator(), FVector(), FVector(0.05,0.05,0.05));
	auto Sphere = Cast<UStaticMeshComponent>(AddComponentByClass(UStaticMeshComponent::StaticClass(), false, LocalTransform, false));
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Sphere->SetStaticMesh(UDFStatics::SPHERE_MESH);

	auto Emitter = Cast<UNiagaraComponent>(AddComponentByClass(UNiagaraComponent::StaticClass(), false, LocalTransform, false));
	Emitter->SetAsset(UDFStatics::TRAIL_SYSTEM);
	Emitter->Activate(true);
}

AFireworkShellBase* AFireworkShellBase::MakeShell(UObject* ContextObject, FVector* Location, FRotator* Rotation, UEffectSystem* System,
                                                  ParameterValueContext* Context, float Delay, float Lifetime, float Velocity)
{
	auto World = GEngine->GetWorldFromContextObject(ContextObject, EGetWorldErrorMode::ReturnNull);

	auto Shell = Cast<AFireworkShellBase>(World->SpawnActor(StaticClass(), Location, Rotation));
	Shell->SpawnData = new EffectSpawnData(System, Context, Shell, Delay, FVector(0), Shell->GetActorForwardVector());
	Shell->SpawnData->Depend();
	Shell->Lifetime = Lifetime;
	Shell->SetActorLocation(*Location);
	auto Component = Cast<UProjectileMovementComponent>(
		Shell->AddComponentByClass(UProjectileMovementComponent::StaticClass(), false, FTransform(), false)
	);
	Component->SetVelocityInLocalSpace(Rotation->RotateVector(FVector(0,0,1)) * Velocity);
	return Shell;
}

void AFireworkShellBase::BeginDestroy()
{
	Super::BeginDestroy();
	DFManaged::SafeRelease(SpawnData);
}
