#include "CBTTask_MoveTo.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
//#include "BehaviorTree/BehaviorTree.h"
//#include "Pet/CPetController.h"
//#include "Pet/CPet.h"
//#include "Enemy/CEnemyController.h"
//#include "Enemy/CEnemy.h"

UCBTTask_MoveTo::UCBTTask_MoveTo()
{
	NodeName = "CMove To";
}

EBTNodeResult::Type UCBTTask_MoveTo::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	AAIController* AIC = Cast<AAIController>(OwnerComp.GetAIOwner());
	CheckNullResult(AIC, EBTNodeResult::Failed);

	ACharacter* AI = Cast<ACharacter>(AIC->GetPawn());
	CheckNullResult(AI, EBTNodeResult::Failed);

	AI->GetCharacterMovement()->StopMovementImmediately();

	return EBTNodeResult::Aborted;

	/*if (OwnerComp.GetRootTree()->GetName() == FName("BT_Pet").ToString())
	{
		ACPetController* AIC = Cast<ACPetController>(OwnerComp.GetAIOwner());
		if (AIC)
		{
			ACPet* Pet = Cast<ACPet>(AIC->GetPawn());
			if (Pet)
			{
				if (Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.State.GetHit"))))
				{
					Pet->GetCharacterMovement()->StopMovementImmediately();

					return EBTNodeResult::Aborted;
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
					return EBTNodeResult::Aborted;
				}
			}
		}
	}*/
}
