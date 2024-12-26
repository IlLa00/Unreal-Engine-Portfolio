#include "CBTTask_MoveTo.h"
#include "Global.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Pet/CPetController.h"
#include "Pet/CPet.h"
#include "Enemy/CEnemyController.h"
#include "Enemy/CEnemy.h"

UCBTTask_MoveTo::UCBTTask_MoveTo()
{
	NodeName = "CMove To";
}

EBTNodeResult::Type UCBTTask_MoveTo::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
				if (Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.State.GetHit"))))
				{
					FinishLatentAbort(OwnerComp);
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
				if (Enemy->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.State.GetHit"))))
				{
					FinishLatentAbort(OwnerComp);
				}
			}
		}
	}

	return EBTNodeResult::Failed;
}
