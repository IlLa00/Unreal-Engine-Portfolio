#include "Weapon/CRocket.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "Weapon/CRPG.h"

ACRocket::ACRocket()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &RootComp, "RootComp");
	CheckNull(RootComp);

	CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp", RootComp);
	CheckNull(MeshComp);

	UStaticMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Assets/Weapon/RPG7_rocket");
	CheckNull(MeshAsset);

	MeshComp->SetStaticMesh(MeshAsset);

	CHelpers::CreateSceneComponent(this, &BoxComp, "BoxComp", MeshComp);
	CheckNull(BoxComp);

	CHelpers::CreateActorComponent(this, &ProjectileComp, "ProjectileComp");
	CheckNull(ProjectileComp);

	CHelpers::GetAsset(&ExplosionParticle, "/Game/Assets/Explosions/Particles/P_ImpactExplosion4");
	CheckNull(ExplosionParticle);

}

void ACRocket::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACRocket::Hit);
}

void ACRocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACRocket::Hit(AActor* OverlappedActor, AActor* OtherActor)
{
	if(ExplosionParticle)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, OtherActor->GetActorLocation());

	ACRPG* RPG = Cast<ACRPG>(GetOwner());
	CheckNull(RPG);

	RPG->SphereTrace(OtherActor->GetActorLocation());

	Destroy();
}

