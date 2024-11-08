#include "Enemy/CMonster.h"
#include "Global.h"
#include "DataAsset/CMonsterMeshDataAsset.h"

ACMonster::ACMonster()
{

}

void ACMonster::SetMesh(FName PlayerArea)
{
	GetMesh()->SetSkeletalMesh(DataAsset->SkeletalMeshAssets[0]);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -80));
	GetMesh()->SetRelativeRotation(FRotator(0, 90, 0));
	GetMesh()->SetAnimClass(DataAsset->AnimClass[0]);
}
