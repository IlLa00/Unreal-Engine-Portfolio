#include "BTNode/CBTService_Boss.h"
#include "Global.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/CEnemyController.h"
#include "Enemy/CBoss.h"
#include "Player/CPlayer.h"
#include "Pet/CPet.h"

UCBTService_Boss::UCBTService_Boss()
{
	NodeName = "BoosService";

	bTickIntervals = true;
}

void UCBTService_Boss::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
	CheckNull(AIC);

	ACBoss* Boss = Cast<ACBoss>(AIC->GetPawn());
	CheckNull(Boss);

	ACPlayer* Player = Cast<ACPlayer>(AIC->GetBlackboardComponent()->GetValueAsObject("PlayerKey"));
	ACPet* Pet = Cast<ACPet>(AIC->GetBlackboardComponent()->GetValueAsObject("PetKey"));

	if (AIC->GetBlackboardComponent()->GetValueAsObject("AttackTargetKey")) // 플레이어가 감지가 되면
	{
		float DistanceToTarget = Boss->GetDistanceTo(Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject("AttackTargetKey")));

		if (DistanceToTarget < 150.f)
		{
			Boss->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag(FName("AI.State.Attack")));
		}
		else
		{
			Boss->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag(FName("AI.State.Approach")));
		}
	}
	else
	{
		Boss->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag("AI.State.Idle"));
	}
	Boss->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag("AI.State.Idle"));
}

void UCBTService_Boss::SetTarget(ACEnemyController* AIC, ACBoss* Boss, ACPlayer* Player, ACPet* Pet)
{
	float DistanceToPlayer = 0.0f;
	float DistanceToPet = 0.0f;

	if (Player != nullptr)
	{
		DistanceToPlayer = Boss->GetDistanceTo(Player);
	}

	if (Pet != nullptr)
	{
		DistanceToPet = Boss->GetDistanceTo(Pet);
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