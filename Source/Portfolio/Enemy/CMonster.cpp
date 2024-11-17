#include "Enemy/CMonster.h"
#include "Global.h"
#include "DataAsset/CMonsterMeshDataAsset.h"

ACMonster::ACMonster()
{

}

void ACMonster::SetMesh(FName PlayerArea) // 여기문제 없음
{
	if (DataAsset && PlayerArea == "Grasslands")
	{
		if (FMath::FRand() < 0.8f) 
		{
			GetMesh()->SetSkeletalMesh(DataAsset->SkeletalMeshAssets[0]);
			GetMesh()->SetRelativeLocation(FVector(0, 0, -80));
			GetMesh()->SetRelativeRotation(FRotator(0, 90, 0));
			
		}
		else
		{
			GetMesh()->SetSkeletalMesh(DataAsset->SkeletalMeshAssets[1]);
			GetMesh()->SetRelativeLocation(FVector(0, 0, -80));
			GetMesh()->SetRelativeRotation(FRotator(0, 90, 0));
			
		}

	}
}

void ACMonster::SetAnimClass()
{
	if (this->GetMesh()->GetSkeletalMeshAsset() == DataAsset->SkeletalMeshAssets[0])
	{
		PrintLine();
		GetMesh()->SetAnimClass(DataAsset->AnimClass[0]);
	}
}
