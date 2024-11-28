#include "Enemy/CMonster.h"
#include "Global.h"
#include "DataAsset/CMonsterMeshDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"

ACMonster::ACMonster()
{
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
}

void ACMonster::BeginPlay()
{
	Super::BeginPlay();

	if (this->GetMesh()->GetSkeletalMeshAsset() == DataAsset->SkeletalMeshAssets[0])
	{
		GetMesh()->SetAnimClass(DataAsset->AnimClass[0]);
	}
	else if (this->GetMesh()->GetSkeletalMeshAsset() == DataAsset->SkeletalMeshAssets[1])
	{
		GetMesh()->SetAnimClass(DataAsset->AnimClass[1]);
	}

	
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
