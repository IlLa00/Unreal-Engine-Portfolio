#include "CBTTaskNode_Attack.h"
#include "Global.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Pet/CPetController.h"
#include "Pet/CPet.h"
#include "Enemy/CEnemyController.h"
#include "Enemy/CEnemy.h"
#include "Components/BoxComponent.h"
#include "AbilitySystemComponent.h"
#include "GAS/GA/AI_Attack.h"

UCBTTaskNode_Attack::UCBTTaskNode_Attack()
{
	NodeName = "Attack";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// 일단 여기서 GA를 발동시키는걸 우선적으로.
	if (OwnerComp.GetRootTree()->GetName() == FName("BT_Pet").ToString())
	{
		ACPetController* AIC = Cast<ACPetController>(OwnerComp.GetAIOwner());
		if (AIC)
		{
			ACPet* Pet = Cast<ACPet>(AIC->GetPawn());
			if (Pet)
			{
				if (Pet->GetAbilitySystemComponent())
				{
					
					Pet->GetAbilitySystemComponent()->TryActivateAbility(Pet->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_Attack::StaticClass())->Handle);
					return EBTNodeResult::InProgress;
				}
			}
		}
	}
	else if (OwnerComp.GetRootTree()->GetName() == FName("BT_Enemy").ToString())
	{
		ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
		if (AIC)
		{
			ACEnemy* Enemy = Cast<ACEnemy>(AIC->GetPawn());
			if (Enemy)
			{
				if (Enemy->GetAbilitySystemComponent())
				{
					Enemy->GetAbilitySystemComponent()->TryActivateAbility(Enemy->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_Attack::StaticClass())->Handle);
					return EBTNodeResult::InProgress;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}

void UCBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (OwnerComp.GetRootTree()->GetName() == FName("BT_Pet").ToString())
	{
		ACPetController* AIC = Cast<ACPetController>(OwnerComp.GetAIOwner());
		if (AIC)
		{
			ACPet* Pet = Cast<ACPet>(AIC->GetPawn());
			if (Pet)
			{
				if (Pet->GetAbilitySystemComponent())
				{
					
					if (!Pet->GetAbilitySystemComponent()->GetCurrentMontage())
					{
						Pet->GetAbilitySystemComponent()->CancelAbilityHandle(Pet->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_Attack::StaticClass())->Handle);
						FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
					}
				}
			}
		}
	}
	else if (OwnerComp.GetRootTree()->GetName() == FName("BT_Enemy").ToString())
	{
		ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
		if (AIC)
		{
			ACEnemy* Enemy = Cast<ACEnemy>(AIC->GetPawn());
			if (Enemy)
			{
				if (Enemy->GetAbilitySystemComponent())
				{
					if (!Enemy->GetAbilitySystemComponent()->GetCurrentMontage())
					{
						Enemy->GetAbilitySystemComponent()->CancelAbilityHandle(Enemy->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_Attack::StaticClass())->Handle);
						FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
					}
				}
			}
		}
	}
	
}

EBTNodeResult::Type UCBTTaskNode_Attack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetRootTree()->GetName() == FName("BT_Pet").ToString())
	{
		ACPetController* AIC = Cast<ACPetController>(OwnerComp.GetAIOwner());
		if (AIC)
		{
			ACPet* Pet = Cast<ACPet>(AIC->GetPawn());
			if (Pet)
			{
				if (Pet->GetAbilitySystemComponent())
				{

					if (!Pet->GetAbilitySystemComponent()->GetCurrentMontage())
					{
						Pet->GetAbilitySystemComponent()->CancelAbilityHandle(Pet->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_Attack::StaticClass())->Handle);
						FinishLatentTask(OwnerComp, EBTNodeResult::Aborted);
					}
				}
			}
		}
	}
	else if (OwnerComp.GetRootTree()->GetName() == FName("BT_Enemy").ToString())
	{
		ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
		if (AIC)
		{
			ACEnemy* Enemy = Cast<ACEnemy>(AIC->GetPawn());
			if (Enemy)
			{
				if (Enemy->GetAbilitySystemComponent())
				{
					if (Enemy->GetAbilitySystemComponent()->GetCurrentMontage())
					{
						Enemy->StopAnimMontage();

						Enemy->GetAbilitySystemComponent()->CancelAbilityHandle(Enemy->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_Attack::StaticClass())->Handle);
						FinishLatentTask(OwnerComp, EBTNodeResult::Aborted);
					}
				}
			}
		}
	}

	return EBTNodeResult::Aborted;
}
