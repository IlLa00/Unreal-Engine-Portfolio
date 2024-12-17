#include "CHookGun.h"
#include "Global.h"

ACHookGun::ACHookGun()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &RootComp, "RootComp");
	CheckNull(RootComp);

	CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp", RootComp);
	CheckNull(MeshComp);

	UStaticMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Assets/Weapon/lowpolyGun");
	CheckNull(MeshAsset);

	MeshComp->SetStaticMesh(MeshAsset);

}

void ACHookGun::BeginPlay()
{
	Super::BeginPlay();

}

void ACHookGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
