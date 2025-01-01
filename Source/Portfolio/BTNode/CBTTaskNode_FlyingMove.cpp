#include "CBTTaskNode_FlyingMove.h"
#include "Global.h"
#include "Enemy/CEnemyController.h"
#include "Enemy/CBoss.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "BehaviorTree/BlackboardComponent.h"

UCBTTaskNode_FlyingMove::UCBTTaskNode_FlyingMove()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_FlyingMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
	CheckNullResult(AIC, EBTNodeResult::Failed);

	ACBoss* Boss = Cast<ACBoss>(AIC->GetPawn());
	CheckNullResult(Boss, EBTNodeResult::Failed);

	CheckNullResult(AIC->GetBlackboardComponent()->GetValueAsObject("AttackTargetKey"), EBTNodeResult::Failed);

	CheckNullResult(Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject("AttackTargetKey")), EBTNodeResult::Failed);

	AIC->SetFocus(Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject("AttackTargetKey")));

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_FlyingMove::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
	CheckNull(AIC);

	ACBoss* Boss = Cast<ACBoss>(AIC->GetPawn());
	CheckNull(Boss);

	Boss->GetFloatingComp()->AddInputVector(Boss->GetActorForwardVector());

	if (Boss->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Attack"))))
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

}

EBTNodeResult::Type UCBTTaskNode_FlyingMove::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
	CheckNullResult(AIC, EBTNodeResult::Failed);

	ACBoss* Boss = Cast<ACBoss>(AIC->GetPawn());
	CheckNullResult(Boss, EBTNodeResult::Failed);

	Boss->GetFloatingComp()->AddInputVector(FVector(0));

	return EBTNodeResult::Aborted;
}
