#include "CBTTaskNode_Attack.h"
#include "Global.h"
#include "AIController.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "GAS/GA/AI_Attack.h"
#include "BehaviorTree/BlackboardComponent.h"

UCBTTaskNode_Attack::UCBTTaskNode_Attack()
{
	NodeName = "Attack";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner()->GetPawn()->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
	{
		IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(OwnerComp.GetAIOwner()->GetPawn());
		CheckNullResult(ASI, EBTNodeResult::Failed);

		OwnerComp.GetAIOwner()->SetFocus(Cast<AActor>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject("AttackTargetKey")));

		ASI->GetAbilitySystemComponent()->TryActivateAbility(ASI->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_Attack::StaticClass())->Handle);

		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Failed;
}

void UCBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (OwnerComp.GetAIOwner()->GetPawn()->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
	{
		IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(OwnerComp.GetAIOwner()->GetPawn());
		CheckNull(ASI);

		if (!ASI->GetAbilitySystemComponent()->GetCurrentMontage())
		{
			ASI->GetAbilitySystemComponent()->CancelAbilityHandle(ASI->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_Attack::StaticClass())->Handle);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}

EBTNodeResult::Type UCBTTaskNode_Attack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner()->GetPawn()->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
	{
		IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(OwnerComp.GetAIOwner()->GetPawn());
		CheckNullResult(ASI, EBTNodeResult::Failed);
		
		if (ASI->GetAbilitySystemComponent()->GetCurrentMontage())
		{
			OwnerComp.GetAIOwner()->ClearFocus(EAIFocusPriority::Default);

			ASI->GetAbilitySystemComponent()->CurrentMontageStop();
			ASI->GetAbilitySystemComponent()->CancelAbilityHandle(ASI->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_Attack::StaticClass())->Handle);

			return EBTNodeResult::Aborted;
		}
	}
	return EBTNodeResult::Failed;
}

