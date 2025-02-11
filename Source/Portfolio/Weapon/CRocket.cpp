#include "Weapon/CRocket.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
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
}

void ACRocket::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACRocket::Overlap);

}

void ACRocket::Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACRPG* RPG = Cast<ACRPG>(GetOwner());
	CheckNull(RPG);

	RPG->SphereTrace(GetActorLocation());

	Destroy();
}

