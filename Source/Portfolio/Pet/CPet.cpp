#include "CPet.h"
#include "Global.h"

ACPet::ACPet()
{
	PrimaryActorTick.bCanEverTick = true;

	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Assets/BattleWizardPolyart/Meshes/WizardSM");
	CheckNull(MeshAsset);

	GetMesh()->SetSkeletalMesh(MeshAsset);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -80));
	GetMesh()->SetRelativeRotation(FRotator(0, 90, 0));

}

void ACPet::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPet::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

