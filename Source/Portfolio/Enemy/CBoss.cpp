#include "Enemy/CBoss.h"
#include "Global.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DataAsset/CBossDataAsset.h"
#include "Enemy/CEnemyController.h"

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
}

void ACBoss::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetAnimClass(AnimClass);
}

void ACBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}
