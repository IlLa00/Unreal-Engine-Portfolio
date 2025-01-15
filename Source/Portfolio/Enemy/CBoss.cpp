#include "Enemy/CBoss.h"
#include "Global.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DataAsset/CBossDataAsset.h"
#include "GAS/Attribute/CAIAttributeSet.h"
#include "Enemy/CEnemyController.h"
#include "Widget/CBossWidget.h"

ACBoss::ACBoss()
{
	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Assets/FourEvilDragonsHP/Meshes/DragonTheUsurper/DragonTheUsurperSK");
	CheckNull(MeshAsset);

	CHelpers::GetClass(&AnimClass, "/Game/Enemy/Boss/ABP_CBoss");
	CheckNull(AnimClass);

	GetMesh()->SetSkeletalMesh(MeshAsset);
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));

	CHelpers::CreateActorComponent(this, &FloatingComp, "FloatingComp");
	CheckNull(FloatingComp);
	
	CHelpers::GetAsset(&BossDataAsset, "/Game/DataAsset/DA_Boss");
	CheckNull(BossDataAsset);

	CHelpers::GetClass(&BossWidgetClass, "/Game/Widget/BP_CBossWidget");
	CheckNull(BossWidgetClass);
}

void ACBoss::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetAnimClass(AnimClass);

	if (AIAttribute)
	{
		AIAttribute->SetBaseHealth(BossDataAsset->BaseHealth);
		AIAttribute->SetBaseDamage(BossDataAsset->BaseDamage);
		AIAttribute->SetCurrentHealth(AIAttribute->GetBaseHealth());
		AIAttribute->SetCurrentDamage(AIAttribute->GetBaseDamage());
	}
}

void ACBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ACBoss::SetWidget(bool state)
{
	if (state)
	{
		if (!BossWidget)
		{
			BossWidget = CreateWidget<UCBossWidget>(GetWorld(), BossWidgetClass);
			CheckNull(BossWidget);

			BossWidget->AddToViewport();
			BossWidget->Update(AIAttribute->GetCurrentHealth(), AIAttribute->GetBaseHealth());
		}
	}
	else
	{
		CheckNull(BossWidget);

		BossWidget->RemoveFromParent();
	}
}
