#include "CAxe.h"
#include "Global.h"

ACAxe::ACAxe()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &RootComp, "RootComp");
	CheckNull(RootComp);

	CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp",RootComp);
	CheckNull(MeshComp);

	UStaticMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Assets/Axe/fire_axe");
	CheckNull(MeshAsset);

	MeshComp->SetStaticMesh(MeshAsset);
}

void ACAxe::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACAxe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

