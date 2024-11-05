#include "CPortal.h"
#include "Global.h"

ACPortal::ACPortal()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp");
	CheckNull(MeshComp);

	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Assets/Portal/Flat_Portal_v2_0_03_unwrapped_realigned_NOT_flipped_03");
	CheckNull(MeshAsset);

	MeshComp->SetSkeletalMesh(MeshAsset);
}

void ACPortal::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

