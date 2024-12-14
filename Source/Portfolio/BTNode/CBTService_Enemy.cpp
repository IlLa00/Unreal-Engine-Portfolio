#include "CBTService_Enemy.h"
#include "Global.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/CEnemyController.h"
#include "Enemy/CEnemy.h"
#include "Player/CPlayer.h"
#include "Pet/CPet.h"

UCBTService_Enemy::UCBTService_Enemy()
{
	NodeName = "EnemyService";

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
	ACPet* Pet = Cast<ACPet>(AIC->GetBlackboardComponent()->GetValueAsObject("PetKey"));

	SetTarget(AIC, Enemy, Player, Pet);

	if (AIC->GetBlackboardComponent()->GetValueAsObject("AttackTargetKey")) // 플레이어가 감지가 되면
	{
		float DistanceToTarget = Enemy->GetDistanceTo(Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject("AttackTargetKey")));

		if (DistanceToTarget < 150.f)
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

void UCBTService_Enemy::SetTarget(ACEnemyController* AIC, ACEnemy* Enemy, ACPlayer* Player, ACPet* Pet)
{
	float DistanceToPlayer = 0.0f;
	float DistanceToPet = 0.0f;

	if (Player != nullptr)
	{
		DistanceToPlayer = Enemy->GetDistanceTo(Player);
	}

	if (Pet != nullptr)
	{
		DistanceToPet = Enemy->GetDistanceTo(Pet);
	}

	if (DistanceToPlayer >= DistanceToPet)
	{
		AIC->GetBlackboardComponent()->SetValueAsObject("AttackTargetKey", Player);
	}
	else
	{
		AIC->GetBlackboardComponent()->SetValueAsObject("AttackTargetKey", Pet);
	}
}