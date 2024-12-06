#include "CBTService_Enemy.h"
#include "Global.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/CEnemyController.h"
#include "Enemy/CEnemy.h"

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

	//if (AIC->GetBlackboardComponent()->GetValueAsObject("PlayerKey")) // 플레이어를 감지하면 쫓는 상태로,
	//{
	//	if (Enemy->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag("AI.State.Idle")))
	//	{
	//		Enemy->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag("AI.State.Idle"));
	//	}
	//	
	//	if (!Enemy->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag("AI.State.Approach")))
	//	{
	//		Enemy->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag("AI.State.Approach"));
	//	}
	//}
	//else
	//{
	//	if (Enemy->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag("AI.State.Approach")))
	//	{
	//		Enemy->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag("AI.State.Approach"));
	//	}

	//	if (!Enemy->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag("AI.State.Idle")))
	//	{
	//		Enemy->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag("AI.State.Idle"));
	//	}
	//}
	if(Enemy->GetTagContainer())
		CLog::Print(Enemy->GetTagContainer().Num()); // 찍히는데 계속 0이뜸, 태그가 안들어가지고있다.

}
