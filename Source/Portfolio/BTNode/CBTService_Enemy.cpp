#include "CBTService_Enemy.h"
#include "Global.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/CEnemyController.h"
#include "Enemy/CEnemy.h"
#include "Player/CPlayer.h"

UCBTService_Enemy::UCBTService_Enemy()
{
	NodeName = "RootService";

	bTickIntervals = true;
}

void UCBTService_Enemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
	CheckNull(AIC);

	ACEnemy* Enemy = Cast<ACEnemy>(AIC->GetPawn());
	CheckNull(Enemy);

	ACPlayer* Player = Cast<ACPlayer>(AIC->GetBlackboardComponent()->GetValueAsObject("PlayerKey"));


	if (Player) // 플레이어가 감지가 되면
	{
		float DistanceToPlayer = Enemy->GetDistanceTo(Player);

		if (DistanceToPlayer < 150.f)
		{
			Enemy->GetTagContainer().Reset();
			Enemy->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag(FName("AI.State.Attack")));
		}
		else
		{
			Enemy->GetTagContainer().Reset();
			Enemy->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag(FName("AI.State.Approach")));
		}
	}
	else
	{
		Enemy->GetTagContainer().Reset();
		Enemy->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag("AI.State.Idle"));
	}
	

}
