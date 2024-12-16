#include "CSword.h"
#include "Global.h"

ACSword::ACSword()
{
	CHelpers::CreateSceneComponent(this, &RootComp, "RootComp");
	CheckNull(RootComp);

	CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp", RootComp);
	CheckNull(MeshComp);

	UStaticMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Assets/KlianLowPoliSwords/Mesh/SM_LargeSword");
	CheckNull(MeshAsset);

	MeshComp->SetStaticMesh(MeshAsset);
	// MeshComp->SetRelativeScale3D(FVector(0.2));

}

void ACSword::BeginPlay()
{
	Super::BeginPlay();
}

void ACSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
