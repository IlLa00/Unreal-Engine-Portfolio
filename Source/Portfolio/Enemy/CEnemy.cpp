#include "CEnemy.h"
#include "Global.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "CEnemyController.h"
#include "GameFramework/CharacterMovementComponent.h"

ACEnemy::ACEnemy()
{
	PrimaryActorTick.bCanEverTick = true;	

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>("ASC");
	CheckNull(ASC);
}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ACEnemyController::StaticClass();

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
	
	ASC->InitAbilityActorInfo(this, this);

}

void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* ACEnemy::GetAbilitySystemComponent() const
{
	return ASC;
}

