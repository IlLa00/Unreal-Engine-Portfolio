#include "Weapon/CRocket.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "Weapon/CRPG.h"
#include "Engine/TriggerVolume.h"

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

	BoxComp->OnComponentHit.AddDynamic(this, &ACRocket::Hit);

}

void ACRocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;

	//FCollisionObjectQueryParams QueryParams;
	//QueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
	//QueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	//QueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);

	FCollisionShape Shape;
	Shape.MakeSphere(1000.f);

	TArray<TEnumAsByte<EObjectTypeQuery>> Query;
	Query.Add(EObjectTypeQuery::ObjectTypeQuery1);
	Query.Add(EObjectTypeQuery::ObjectTypeQuery2);
	Query.Add(EObjectTypeQuery::ObjectTypeQuery3);

	TArray<AActor*> Ignores;
	Ignores.Add(this);
	Ignores.Add(GetOwner());
	Ignores.Add(GetOwner()->GetOwner());



	if (UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 10.f, 100.f, Query, false, Ignores, EDrawDebugTrace::ForOneFrame, HitResult, true))
	{
		if (HitResult.GetActor()->IsA<ATriggerVolume>()) return;
		if (HitResult.GetActor()->IsA<ACRPG>()) return;


		if (ExplosionParticle)
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, HitResult.Location);

		ACRPG* RPG = Cast<ACRPG>(GetOwner());
		CheckNull(RPG);

		RPG->SphereTrace(HitResult.Location);

		Destroy();
	}

}

void ACRocket::Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	PrintLine();
}

