#include "CBTTaskNode_Attack.h"
#include "Global.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Pet/CPetController.h"
#include "Pet/CPet.h"
#include "Enemy/CEnemyController.h"
#include "Enemy/CEnemy.h"
#include "Enemy/CBoss.h"
#include "Components/BoxComponent.h"
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
					AIC->SetFocus(Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject("EnemyKey")));

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
					AIC->SetFocus(Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject("AttackTargetKey")));

					Enemy->GetAbilitySystemComponent()->TryActivateAbility(Enemy->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_Attack::StaticClass())->Handle);
					return EBTNodeResult::InProgress;
				}
			}
		}
	}
	else if (OwnerComp.GetRootTree()->GetName() == FName("BT_Boss").ToString())
	{
		ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
		if (AIC)
		{
			ACBoss* Boss = Cast<ACBoss>(AIC->GetPawn());
			if (Boss)
			{
				if (Boss->GetAbilitySystemComponent())
				{
					AIC->SetFocus(Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject("AttackTargetKey")));

					Boss->GetAbilitySystemComponent()->TryActivateAbility(Boss->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_Attack::StaticClass())->Handle);

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
	else if (OwnerComp.GetRootTree()->GetName() == FName("BT_Boss").ToString())
	{
		ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
		if (AIC)
		{
			ACBoss* Boss = Cast<ACBoss>(AIC->GetPawn());
			if (Boss)
			{
				if (Boss->GetAbilitySystemComponent())
				{
					if (!Boss->GetCurrentMontage())
					{
						Boss->GetAbilitySystemComponent()->CancelAbilityHandle(Boss->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_Attack::StaticClass())->Handle);

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
					if (Pet->GetAbilitySystemComponent()->GetCurrentMontage())
					{
						AIC->ClearFocus(EAIFocusPriority::Default);

						Pet->GetAbilitySystemComponent()->CancelAbilityHandle(Pet->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_Attack::StaticClass())->Handle);

						return EBTNodeResult::Aborted;
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
					if (Enemy->GetCurrentMontage())
					{
						AIC->ClearFocus(EAIFocusPriority::Default);

						Enemy->StopAnimMontage();

						Enemy->GetAbilitySystemComponent()->CancelAbilityHandle(Enemy->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_Attack::StaticClass())->Handle);

						return EBTNodeResult::Aborted;
					}
				}
			}
		}
	}
	else if (OwnerComp.GetRootTree()->GetName() == FName("BT_Boss").ToString())
	{
		ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
		if (AIC)
		{
			ACBoss* Boss = Cast<ACBoss>(AIC->GetPawn());
			if (Boss)
			{
				if (Boss->GetAbilitySystemComponent())
				{
					if (Boss->GetCurrentMontage())
					{
						AIC->ClearFocus(EAIFocusPriority::Default);

						Boss->StopAnimMontage();

						Boss->GetAbilitySystemComponent()->CancelAbilityHandle(Boss->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_Attack::StaticClass())->Handle);

						return EBTNodeResult::Aborted;
					}
				}
			}
		}
	}

	return EBTNodeResult::Failed;
}

