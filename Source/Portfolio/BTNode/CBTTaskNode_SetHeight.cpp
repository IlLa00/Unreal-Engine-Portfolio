#include "CBTTaskNode_SetHeight.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Enemy/CEnemyController.h"
#include "Enemy/CBoss.h"

UCBTTaskNode_SetHeight::UCBTTaskNode_SetHeight()
{
	NodeName = "SetHeight";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_SetHeight::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);



	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_SetHeight::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
	CheckNull(AIC);

	ACBoss* Boss = Cast<ACBoss>(AIC->GetPawn());
	CheckNull(Boss);

	if (Boss->GetCharacterMovement()->Velocity.Z < Height)
	{
		Boss->GetCharacterMovement()->Velocity.Z += 1.f;
	}
	else
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
