#include "CEnemy.h"
#include "Global.h"
#include "CEnemyController.h"
#include "GameFramework/CharacterMovementComponent.h"

ACEnemy::ACEnemy()
{
	PrimaryActorTick.bCanEverTick = true;	

}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ACEnemyController::StaticClass();

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
	
	
}

void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

