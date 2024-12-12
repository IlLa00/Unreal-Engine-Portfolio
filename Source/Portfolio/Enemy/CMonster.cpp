#include "CMonster.h"
#include "Global.h"
#include "Components/TextRenderComponent.h"
#include "DataAsset/CMonsterMeshDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/Attribute/CMonsterAttributeSet.h"

ACMonster::ACMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MaxWalkSpeed = 200.f; // 이거 수정해야할지도?
}

void ACMonster::BeginPlay()
{
	Super::BeginPlay();

	if (this->GetMesh()->GetSkeletalMeshAsset() == DataAsset->Datas[0].SkeletalMeshAssets)
	{
		GetMesh()->SetAnimClass(DataAsset->Datas[0].AnimClass);
		if (Attribute)
		{
			Attribute->SetBaseHealth(DataAsset->Datas[0].BaseHealth);
			Attribute->SetBaseDamage(DataAsset->Datas[0].BaseDamage);
		}
	}
	else if (this->GetMesh()->GetSkeletalMeshAsset() == DataAsset->Datas[1].SkeletalMeshAssets)
	{
		GetMesh()->SetAnimClass(DataAsset->Datas[1].AnimClass);
		if (Attribute)
		{
			Attribute->SetBaseHealth(DataAsset->Datas[1].BaseHealth);
			Attribute->SetBaseDamage(DataAsset->Datas[1].BaseDamage);
		}
	};
}

void ACMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACMonster::SetMesh(FName PlayerArea) 
{
	if (DataAsset && PlayerArea == "Grasslands")
	{
		if (FMath::FRand() < 0.5f) 
		{
			GetMesh()->SetSkeletalMesh(DataAsset->Datas[0].SkeletalMeshAssets);
			GetMesh()->SetRelativeLocation(FVector(0, 0, -80));
			GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
		}
		else
		{
			GetMesh()->SetSkeletalMesh(DataAsset->Datas[1].SkeletalMeshAssets);
			GetMesh()->SetRelativeLocation(FVector(0, 0, -80));
			GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
		}
	}
}
