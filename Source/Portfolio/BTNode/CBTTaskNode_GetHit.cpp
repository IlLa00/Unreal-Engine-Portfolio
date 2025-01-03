#include "CBTTaskNode_GetHit.h"
#include "Global.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Pet/CPetController.h"
#include "Pet/CPet.h"
#include "Enemy/CEnemy.h"
#include "Enemy/CEnemyController.h"
#include "AbilitySystemComponent.h"
#include "GAS/GA/AI_Attack.h"
#include "GAS/GA/AI_GetHit.h"
#include "GameFramework/CharacterMovementComponent.h"

UCBTTaskNode_GetHit::UCBTTaskNode_GetHit()
{
	NodeName = "Attack";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_GetHit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetRootTree()->GetName() == FName("BT_Pet").ToString())
	{
		ACPetController* AIC = Cast<ACPetController>(OwnerComp.GetAIOwner());
		CheckNullResult(AIC, EBTNodeResult::Failed);

		ACPet* Pet = Cast<ACPet>(AIC->GetPawn());
		CheckNullResult(Pet, EBTNodeResult::Failed);
		CheckNullResult(Pet->GetAbilitySystemComponent(), EBTNodeResult::Failed);

		Pet->GetAbilitySystemComponent()->TryActivateAbility(Pet->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_GetHit::StaticClass())->Handle);

		return EBTNodeResult::InProgress;
	}
	else if (OwnerComp.GetRootTree()->GetName() == FName("BT_Enemy").ToString())
	{
		ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
		CheckNullResult(AIC, EBTNodeResult::Failed);

		ACEnemy* Enemy = Cast<ACEnemy>(AIC->GetPawn());
		CheckNullResult(Enemy, EBTNodeResult::Failed);
		CheckNullResult(Enemy->GetAbilitySystemComponent(), EBTNodeResult::Failed);

		Enemy->GetAbilitySystemComponent()->TryActivateAbility(Enemy->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_GetHit::StaticClass())->Handle);

		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Failed;
}

void UCBTTaskNode_GetHit::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (OwnerComp.GetRootTree()->GetName() == FName("BT_Pet").ToString())
	{
		ACPetController* AIC = Cast<ACPetController>(OwnerComp.GetAIOwner());
		CheckNull(AIC);

		ACPet* Pet = Cast<ACPet>(AIC->GetPawn());
		CheckNull(Pet);
		CheckNull(Pet->GetAbilitySystemComponent());

		if (!Pet->GetCurrentMontage())
		{
			Pet->GetAbilitySystemComponent()->CancelAbilityHandle(Pet->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_GetHit::StaticClass())->Handle);

			Pet->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.GetHit")));

			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
	else if (OwnerComp.GetRootTree()->GetName() == FName("BT_Enemy").ToString())
	{
		ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
		CheckNull(AIC);

		ACEnemy* Enemy = Cast<ACEnemy>(AIC->GetPawn());
		CheckNull(Enemy);
		CheckNull(Enemy->GetAbilitySystemComponent());

		if (!Enemy->GetCurrentMontage())
		{
			Enemy->GetAbilitySystemComponent()->CancelAbilityHandle(Enemy->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_GetHit::StaticClass())->Handle);

			Enemy->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.GetHit")));

			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}

EBTNodeResult::Type UCBTTaskNode_GetHit::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetRootTree()->GetName() == FName("BT_Pet").ToString())
	{
		ACPetController* AIC = Cast<ACPetController>(OwnerComp.GetAIOwner());
		CheckNullResult(AIC, EBTNodeResult::Failed);

		ACPet* Pet = Cast<ACPet>(AIC->GetPawn());
		CheckNullResult(Pet, EBTNodeResult::Failed);
		CheckNullResult(Pet->GetAbilitySystemComponent(), EBTNodeResult::Failed);

		if (Pet->GetCurrentMontage())
			Pet->StopAnimMontage();

		Pet->GetAbilitySystemComponent()->CancelAbilityHandle(Pet->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_GetHit::StaticClass())->Handle);

		return EBTNodeResult::Aborted;
	}
	else if (OwnerComp.GetRootTree()->GetName() == FName("BT_Enemy").ToString())
	{
		ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
		CheckNullResult(AIC, EBTNodeResult::Failed);
		{
			ACEnemy* Enemy = Cast<ACEnemy>(AIC->GetPawn());
			CheckNullResult(Enemy, EBTNodeResult::Failed);
			CheckNullResult(Enemy->GetAbilitySystemComponent(), EBTNodeResult::Failed);

			if (Enemy->GetCurrentMontage())
				Enemy->StopAnimMontage();

			Enemy->GetAbilitySystemComponent()->CancelAbilityHandle(Enemy->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_GetHit::StaticClass())->Handle);

			return EBTNodeResult::Aborted;
		}
	}

	return EBTNodeResult::Failed;
}
