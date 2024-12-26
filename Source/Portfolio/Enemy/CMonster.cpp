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
	if (this->GetMesh()->GetSkeletalMeshAsset() == DataAsset->Datas[0].SkeletalMeshAssets)
	{
		GetMesh()->SetAnimClass(DataAsset->Datas[Index].AnimClass);
		if (Attribute)
		{
			Attribute->SetBaseHealth(DataAsset->Datas[Index].BaseHealth);
			Attribute->SetBaseDamage(DataAsset->Datas[Index].BaseDamage);

			Attribute->SetCurrentHealth(Attribute->GetBaseHealth());
			Attribute->SetCurrentDamage(Attribute->GetBaseDamage());
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
	}
	else if (this->GetMesh()->GetSkeletalMeshAsset() == DataAsset->Datas[2].SkeletalMeshAssets)
	{
		GetMesh()->SetAnimClass(DataAsset->Datas[Index].AnimClass);
		if (Attribute)
		{
			Attribute->SetBaseHealth(DataAsset->Datas[Index].BaseHealth);
			Attribute->SetBaseDamage(DataAsset->Datas[Index].BaseDamage);

			Attribute->SetCurrentHealth(Attribute->GetBaseHealth());
			Attribute->SetCurrentDamage(Attribute->GetBaseDamage());
		}
	}
	else if (this->GetMesh()->GetSkeletalMeshAsset() == DataAsset->Datas[3].SkeletalMeshAssets)
	{
		GetMesh()->SetAnimClass(DataAsset->Datas[Index].AnimClass);
		if (Attribute)
		{
			Attribute->SetBaseHealth(DataAsset->Datas[Index].BaseHealth);
			Attribute->SetBaseDamage(DataAsset->Datas[Index].BaseDamage);

			Attribute->SetCurrentHealth(Attribute->GetBaseHealth());
			Attribute->SetCurrentDamage(Attribute->GetBaseDamage());
		}
	}
	else if (this->GetMesh()->GetSkeletalMeshAsset() == DataAsset->Datas[4].SkeletalMeshAssets)
	{
		GetMesh()->SetAnimClass(DataAsset->Datas[Index].AnimClass);
		if (Attribute)
		{
			Attribute->SetBaseHealth(DataAsset->Datas[Index].BaseHealth);
			Attribute->SetBaseDamage(DataAsset->Datas[Index].BaseDamage);

			Attribute->SetCurrentHealth(Attribute->GetBaseHealth());
			Attribute->SetCurrentDamage(Attribute->GetBaseDamage());
		}
	}
	else if (this->GetMesh()->GetSkeletalMeshAsset() == DataAsset->Datas[5].SkeletalMeshAssets)
	{
		GetMesh()->SetAnimClass(DataAsset->Datas[Index].AnimClass);
		if (Attribute)
		{
			Attribute->SetBaseHealth(DataAsset->Datas[Index].BaseHealth);
			Attribute->SetBaseDamage(DataAsset->Datas[Index].BaseDamage);

			Attribute->SetCurrentHealth(Attribute->GetBaseHealth());
			Attribute->SetCurrentDamage(Attribute->GetBaseDamage());
		}
	}
	else if (this->GetMesh()->GetSkeletalMeshAsset() == DataAsset->Datas[6].SkeletalMeshAssets)
	{
		GetMesh()->SetAnimClass(DataAsset->Datas[Index].AnimClass);
		if (Attribute)
		{
			Attribute->SetBaseHealth(DataAsset->Datas[Index].BaseHealth);
			Attribute->SetBaseDamage(DataAsset->Datas[Index].BaseDamage);

			Attribute->SetCurrentHealth(Attribute->GetBaseHealth());
			Attribute->SetCurrentDamage(Attribute->GetBaseDamage());
		}
	}
	else if (this->GetMesh()->GetSkeletalMeshAsset() == DataAsset->Datas[7].SkeletalMeshAssets)
	{
		GetMesh()->SetAnimClass(DataAsset->Datas[Index].AnimClass);
		if (Attribute)
		{
			Attribute->SetBaseHealth(DataAsset->Datas[Index].BaseHealth);
			Attribute->SetBaseDamage(DataAsset->Datas[Index].BaseDamage);

			Attribute->SetCurrentHealth(Attribute->GetBaseHealth());
			Attribute->SetCurrentDamage(Attribute->GetBaseDamage());
		}
	}

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
	else if (DataAsset && PlayerArea == "RockPlain")
	{
		if (FMath::FRand() < 0.5f)
		{
			Index = 2;
		}
		else
		{
			Index = 3;
		}
		GetMesh()->SetSkeletalMesh(DataAsset->Datas[Index].SkeletalMeshAssets);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -80));
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	}
	else if (DataAsset && PlayerArea == "BamBooForest")
	{
		if (FMath::FRand() < 0.5f)
		{
			Index = 4;
		}
		else
		{
			Index = 5;
		}
		GetMesh()->SetSkeletalMesh(DataAsset->Datas[Index].SkeletalMeshAssets);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -80));
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	}
	else if (DataAsset && PlayerArea == "Cliff")
	{
		if (FMath::FRand() < 0.5f)
		{
			Index = 4;
		}
		else
		{
			Index = 3;
		}
		GetMesh()->SetSkeletalMesh(DataAsset->Datas[Index].SkeletalMeshAssets);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -80));
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	}

}
