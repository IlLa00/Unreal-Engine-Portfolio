#include "CBTTaskNode_Dead.h"
#include "Global.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AbilitySystemComponent.h"
#include "Pet/CPetController.h"
#include "Pet/CPet.h"
#include "Enemy/CEnemyController.h"
#include "Enemy/CEnemy.h"
#include "GAS/GA/AI_Dead.h"

UCBTTaskNode_Dead::UCBTTaskNode_Dead()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Dead::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetRootTree()->GetName() == FName("BT_Enemy").ToString())
	{
		ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
		if (AIC)
		{
			ACEnemy* Enemy = Cast<ACEnemy>(AIC->GetPawn());
			if (Enemy)
			{
				if (Enemy->GetAbilitySystemComponent())
				{
					Enemy->GetAbilitySystemComponent()->TryActivateAbility(Enemy->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_Dead::StaticClass())->Handle);

					return EBTNodeResult::Succeeded;
				}
			}
		}
	}

	return EBTNodeResult::Failed;
}
