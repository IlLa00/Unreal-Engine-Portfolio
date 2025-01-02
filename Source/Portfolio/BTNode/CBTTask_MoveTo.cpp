#include "CBTTask_MoveTo.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "Interface/CAIInterface.h"

UCBTTask_MoveTo::UCBTTask_MoveTo()
{
	NodeName = "CMove To";
}

EBTNodeResult::Type UCBTTask_MoveTo::PerformMoveTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::PerformMoveTask(OwnerComp, NodeMemory);

	AAIController* AIC = Cast<AAIController>(OwnerComp.GetAIOwner());
	CheckNullResult(AIC, EBTNodeResult::Failed);

	ICAIInterface* AI = Cast<ICAIInterface>(AIC->GetPawn());
	CheckNullResult(AI, EBTNodeResult::Failed);

	if (Result == EBTNodeResult::InProgress)
	{
		if (!AI->GetTagContainer().HasTag((FGameplayTag::RequestGameplayTag(FName("AI.Action.Approach")))))
		{
			return EBTNodeResult::Aborted;
		}
	}

	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UCBTTask_MoveTo::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::AbortTask(OwnerComp, NodeMemory);

	AAIController* AIC = Cast<AAIController>(OwnerComp.GetAIOwner());
	CheckNullResult(AIC, EBTNodeResult::Failed);

	ACharacter* AI = Cast<ACharacter>(AIC->GetPawn());
	CheckNullResult(AI, EBTNodeResult::Failed);

	AI->GetCharacterMovement()->StopMovementImmediately();

	PrintLine();

	return Result;
}
