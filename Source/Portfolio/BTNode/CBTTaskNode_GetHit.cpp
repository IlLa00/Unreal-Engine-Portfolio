#include "CBTTaskNode_GetHit.h"
#include "Global.h"
#include "AIController.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Interface/CAIInterface.h"
#include "GAS/GA/AI_Attack.h"
#include "GAS/GA/AI_GetHit.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UCBTTaskNode_GetHit::UCBTTaskNode_GetHit()
{
	NodeName = "Attack";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_GetHit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner()->GetPawn()->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
	{
		IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(OwnerComp.GetAIOwner()->GetPawn());
		CheckNullResult(ASI, EBTNodeResult::Failed);

		ASI->GetAbilitySystemComponent()->TryActivateAbility(ASI->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_GetHit::StaticClass())->Handle);

		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}

void UCBTTaskNode_GetHit::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (OwnerComp.GetAIOwner()->GetPawn()->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
	{
		IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(OwnerComp.GetAIOwner()->GetPawn());
		CheckNull(ASI);

		if (!ASI->GetAbilitySystemComponent()->GetCurrentMontage())
		{
			ASI->GetAbilitySystemComponent()->CancelAbilityHandle(ASI->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_GetHit::StaticClass())->Handle);

			ICAIInterface* AI = Cast<ICAIInterface>(OwnerComp.GetAIOwner()->GetCharacter());
			CheckNull(AI);

			AI->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.GetHit")));

			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}

EBTNodeResult::Type UCBTTaskNode_GetHit::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner()->GetPawn()->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
	{
		IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(OwnerComp.GetAIOwner()->GetPawn());
		CheckNullResult(ASI, EBTNodeResult::Failed);

		if (ASI->GetAbilitySystemComponent()->GetCurrentMontage())
			ASI->GetAbilitySystemComponent()->CurrentMontageStop();

		ASI->GetAbilitySystemComponent()->CancelAbilityHandle(ASI->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_GetHit::StaticClass())->Handle);

		ICAIInterface* AI = Cast<ICAIInterface>(OwnerComp.GetAIOwner()->GetCharacter());
		CheckNullResult(AI, EBTNodeResult::Failed);

		AI->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.GetHit")));

		return EBTNodeResult::Aborted;
	}
	return EBTNodeResult::Failed;
}
