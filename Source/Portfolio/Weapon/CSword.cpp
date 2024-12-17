#include "CSword.h"
#include "Global.h"
#include "GameplayTagContainer.h"

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
}

void ACSword::BeginPlay()
{
	Super::BeginPlay();

	if (Tag.IsValid())
	{
		PrintLine();
		CLog::Print(Tag.ToString());
	}
	else
		PrintLine();
}

void ACSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
