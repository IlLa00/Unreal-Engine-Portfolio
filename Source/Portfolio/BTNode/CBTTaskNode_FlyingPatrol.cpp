#include "CBTTaskNode_FlyingPatrol.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Enemy/CEnemyController.h"
#include "Enemy/CBoss.h"
#include "DataAsset/CBossDataAsset.h"

UCBTTaskNode_FlyingPatrol::UCBTTaskNode_FlyingPatrol()
{
	NodeName = "FlyingPatrol";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_FlyingPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
	CheckNullResult(AIC, EBTNodeResult::Failed);

	ACBoss* Boss = Cast<ACBoss>(AIC->GetPawn());
	CheckNullResult(Boss, EBTNodeResult::Failed);

	Boss->GetFloatingComp()->MaxSpeed = 800.f;
	Boss->SetActorRotation(FRotator(0, FMath::RandRange(0, 360), 0)); 

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_FlyingPatrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
	CheckNull(AIC);

	ACBoss* Boss = Cast<ACBoss>(AIC->GetPawn());
	CheckNull(Boss);

	Boss->GetFloatingComp()->AddInputVector(FVector(Boss->GetActorForwardVector())); 
}

EBTNodeResult::Type UCBTTaskNode_FlyingPatrol::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
	CheckNullResult(AIC, EBTNodeResult::Failed);

	ACBoss* Boss = Cast<ACBoss>(AIC->GetPawn());
	CheckNullResult(Boss, EBTNodeResult::Failed);
	
	Boss->GetFloatingComp()->StopMovementImmediately();

	return EBTNodeResult::Aborted;
}
