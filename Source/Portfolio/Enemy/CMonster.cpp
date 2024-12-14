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

	// 여기 수정할 수 있을듯
	if (this->GetMesh()->GetSkeletalMeshAsset() == DataAsset->Datas[0].SkeletalMeshAssets)
	{
		GetMesh()->SetAnimClass(DataAsset->Datas[Index].AnimClass);
		if (Attribute)
		{
			Attribute->SetBaseHealth(DataAsset->Datas[Index].BaseHealth);
			Attribute->SetBaseDamage(DataAsset->Datas[Index].BaseDamage);

			Attribute->SetCurrentHealth(Attribute->GetBaseHealth());
			Attribute->SetCurrentDamage(Attribute->GetBaseDamage());

			CLog::Print(Attribute->GetCurrentHealth());
			CLog::Print(Attribute->GetCurrentDamage());
		}
	}
	else if (this->GetMesh()->GetSkeletalMeshAsset() == DataAsset->Datas[1].SkeletalMeshAssets)
	{
		GetMesh()->SetAnimClass(DataAsset->Datas[Index].AnimClass);
		if (Attribute)
		{
			Attribute->SetBaseHealth(DataAsset->Datas[Index].BaseHealth);
			Attribute->SetBaseDamage(DataAsset->Datas[Index].BaseDamage);

			Attribute->SetCurrentHealth(Attribute->GetBaseHealth());
			Attribute->SetCurrentDamage(Attribute->GetBaseDamage());
		}
	};

	Super::BeginPlay();
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
			Index = 0;
		}
		else
		{
			Index = 1;
		}
		GetMesh()->SetSkeletalMesh(DataAsset->Datas[Index].SkeletalMeshAssets);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -80));
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	}
}
