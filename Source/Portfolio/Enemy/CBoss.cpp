#include "Enemy/CBoss.h"
#include "Global.h"

ACBoss::ACBoss()
{
	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Assets/FourEvilDragonsHP/Meshes/DragonTheUsurper/DragonTheUsurperSK");
	CheckNull(MeshAsset);

	GetMesh()->SetSkeletalMesh(MeshAsset);
}