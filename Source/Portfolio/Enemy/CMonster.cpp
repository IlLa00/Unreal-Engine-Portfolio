#include "CMonster.h"
#include "Global.h"
#include "Components/TextRenderComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "DataAsset/CMonsterMeshDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/Attribute/CAIAttributeSet.h"
#include "Widget/CEnemyHealthWidget.h"
#include "Player/CPlayer.h"
#include "Pet/CPet.h"
#include "GAS/Attribute/CCharacterAttributeSet.h"
#include "Enemy/CEnemyController.h"

ACMonster::ACMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::GetAsset(&DataAsset, "/Game/DataAsset/DA_Monster");
	CheckNull(DataAsset);

	CHelpers::CreateSceneComponent(this, &HealthWidgetComp, "HealthWidgetComp", GetMesh());
	CheckNull(HealthWidgetComp);

	CHelpers::CreateSceneComponent(this, &AttackComp, "AttackComp", GetMesh());
	CheckNull(AttackComp);

	TSubclassOf<UCEnemyHealthWidget> HealthWidgetClass;
	CHelpers::GetClass(&HealthWidgetClass, "/Game/Widget/WB_CEnemyHealthWidget");
	HealthWidgetComp->SetWidgetClass(HealthWidgetClass);
	HealthWidgetComp->SetRelativeLocation(FVector(0, 0, 190));
	HealthWidgetComp->SetDrawSize(FVector2D(120, 20));
	HealthWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);

	GetCharacterMovement()->MaxWalkSpeed = 200.f; // 이거 수정해야할지도?
}

void ACMonster::BeginPlay()
{
	Super::BeginPlay();

	if (this->GetMesh()->GetSkeletalMeshAsset() == DataAsset->Datas[0].SkeletalMeshAssets)
	{
		GetMesh()->SetAnimClass(DataAsset->Datas[Index].AnimClass);
		if (ASC && AIAttribute)
		{
			AIAttribute->SetBaseHealth(DataAsset->Datas[Index].BaseHealth);
			AIAttribute->SetBaseDamage(DataAsset->Datas[Index].BaseDamage);

			AIAttribute->SetCurrentHealth(AIAttribute->GetBaseHealth());
			AIAttribute->SetCurrentDamage(AIAttribute->GetBaseDamage());
		}
	}
	else if (this->GetMesh()->GetSkeletalMeshAsset() == DataAsset->Datas[1].SkeletalMeshAssets)
	{
		GetMesh()->SetAnimClass(DataAsset->Datas[Index].AnimClass);
		if (ASC && AIAttribute)
		{
			AIAttribute->SetBaseHealth(DataAsset->Datas[Index].BaseHealth);
			AIAttribute->SetBaseDamage(DataAsset->Datas[Index].BaseDamage);

			AIAttribute->SetCurrentHealth(AIAttribute->GetBaseHealth());
			AIAttribute->SetCurrentDamage(AIAttribute->GetBaseDamage());
		}
	}
	else if (this->GetMesh()->GetSkeletalMeshAsset() == DataAsset->Datas[2].SkeletalMeshAssets)
	{
		GetMesh()->SetAnimClass(DataAsset->Datas[Index].AnimClass);
		if (ASC && AIAttribute)
		{
			AIAttribute->SetBaseHealth(DataAsset->Datas[Index].BaseHealth);
			AIAttribute->SetBaseDamage(DataAsset->Datas[Index].BaseDamage);

			AIAttribute->SetCurrentHealth(AIAttribute->GetBaseHealth());
			AIAttribute->SetCurrentDamage(AIAttribute->GetBaseDamage());
		}
	}
	else if (this->GetMesh()->GetSkeletalMeshAsset() == DataAsset->Datas[3].SkeletalMeshAssets)
	{
		GetMesh()->SetAnimClass(DataAsset->Datas[Index].AnimClass);
		if (ASC && AIAttribute)
		{
			AIAttribute->SetBaseHealth(DataAsset->Datas[Index].BaseHealth);
			AIAttribute->SetBaseDamage(DataAsset->Datas[Index].BaseDamage);

			AIAttribute->SetCurrentHealth(AIAttribute->GetBaseHealth());
			AIAttribute->SetCurrentDamage(AIAttribute->GetBaseDamage());
		}
	}
	else if (this->GetMesh()->GetSkeletalMeshAsset() == DataAsset->Datas[4].SkeletalMeshAssets)
	{
		GetMesh()->SetAnimClass(DataAsset->Datas[Index].AnimClass);
		if (ASC && AIAttribute)
		{
			AIAttribute->SetBaseHealth(DataAsset->Datas[Index].BaseHealth);
			AIAttribute->SetBaseDamage(DataAsset->Datas[Index].BaseDamage);

			AIAttribute->SetCurrentHealth(AIAttribute->GetBaseHealth());
			AIAttribute->SetCurrentDamage(AIAttribute->GetBaseDamage());
		}
	}
	else if (this->GetMesh()->GetSkeletalMeshAsset() == DataAsset->Datas[5].SkeletalMeshAssets)
	{
		GetMesh()->SetAnimClass(DataAsset->Datas[Index].AnimClass);
		if (ASC && AIAttribute)
		{
			AIAttribute->SetBaseHealth(DataAsset->Datas[Index].BaseHealth);
			AIAttribute->SetBaseDamage(DataAsset->Datas[Index].BaseDamage);

			AIAttribute->SetCurrentHealth(AIAttribute->GetBaseHealth());
			AIAttribute->SetCurrentDamage(AIAttribute->GetBaseDamage());
		}
	}
	else if (this->GetMesh()->GetSkeletalMeshAsset() == DataAsset->Datas[6].SkeletalMeshAssets)
	{
		GetMesh()->SetAnimClass(DataAsset->Datas[Index].AnimClass);
		if (ASC && AIAttribute)
		{
			AIAttribute->SetBaseHealth(DataAsset->Datas[Index].BaseHealth);
			AIAttribute->SetBaseDamage(DataAsset->Datas[Index].BaseDamage);

			AIAttribute->SetCurrentHealth(AIAttribute->GetBaseHealth());
			AIAttribute->SetCurrentDamage(AIAttribute->GetBaseDamage());
		}
	}
	else if (this->GetMesh()->GetSkeletalMeshAsset() == DataAsset->Datas[7].SkeletalMeshAssets)
	{
		GetMesh()->SetAnimClass(DataAsset->Datas[Index].AnimClass);
		if (ASC && AIAttribute)
		{
			AIAttribute->SetBaseHealth(DataAsset->Datas[Index].BaseHealth);
			AIAttribute->SetBaseDamage(DataAsset->Datas[Index].BaseDamage);

			AIAttribute->SetCurrentHealth(AIAttribute->GetBaseHealth());
			AIAttribute->SetCurrentDamage(AIAttribute->GetBaseDamage());
		}
	}

	if (HealthWidgetComp)
	{
		HealthWidgetComp->InitWidget();
	}

	HealthWidgetObject = Cast<UCEnemyHealthWidget>(HealthWidgetComp->GetUserWidgetObject());
	

	if (HealthWidgetObject)
		HealthWidgetObject->Update(AIAttribute->GetCurrentHealth(), AIAttribute->GetBaseHealth());

	if (AttackComp)
	{
		AttackComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "AttackSocket");
		AttackComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		AttackComp->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy::BeginOverlap);
	}

}

void ACMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Distance = GetDistanceTo(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (Distance > 30000.f)
	{
		ACEnemyController* AIC = Cast<ACEnemyController>(GetController());
		CheckNull(AIC);

		AIC->OnUnPossess();
		Destroy();
	}
}

void ACMonster::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<ACEnemy>())
		return;

	if (OtherActor->IsA<ACPlayer>())
	{
		ACPlayer* Player = Cast<ACPlayer>(OtherActor);
		CheckNull(Player);

		Player->GetAttributeSet()->SetCurrentHealth(Player->GetAttributeSet()->GetCurrentHealth() - AIAttribute->GetCurrentDamage());
	}
	else if (OtherActor->IsA<ACPet>())
	{
		ACPet* Pet = Cast<ACPet>(OtherActor);
		CheckNull(Pet);

		Pet->GetAIAttributeSet()->SetCurrentHealth(Pet->GetAIAttributeSet()->GetCurrentHealth() - AIAttribute->GetCurrentDamage());
	}


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
	else if (DataAsset && PlayerArea == "Rock Plain")
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
	else if (DataAsset && PlayerArea == "Bamboo Forest")
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
	else if (DataAsset && PlayerArea == "Dessert")
	{
		if (FMath::FRand() < 0.5f)
		{
			Index = 6;
		}
		else
		{
			Index = 7;
		}
		GetMesh()->SetSkeletalMesh(DataAsset->Datas[Index].SkeletalMeshAssets);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -80));
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	}
	else if (DataAsset && PlayerArea == "Cliff")
	{
		if (FMath::FRand() < 0.5f)
		{
			Index = 5;
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
