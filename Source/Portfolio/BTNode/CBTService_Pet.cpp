#include "CBTService_Pet.h"
#include "Global.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Pet/CPetController.h"
#include "Pet/CPet.h"
#include "Enemy/CEnemy.h"
#include "Enemy/CBoss.h"
#include "Player/CPlayer.h"

UCBTService_Pet::UCBTService_Pet()
{
	NodeName = "RootService";

	bTickIntervals = true;
}

void UCBTService_Pet::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACPetController* AIC = Cast<ACPetController>(OwnerComp.GetAIOwner());
	CheckNull(AIC);

	ACPet* Pet = Cast<ACPet>(AIC->GetPawn());
	CheckNull(Pet);

	ACPlayer* Player = Cast<ACPlayer>(AIC->GetBlackboardComponent()->GetValueAsObject("PlayerKey"));
	ACEnemy* Enemy = Cast<ACEnemy>(AIC->GetBlackboardComponent()->GetValueAsObject("EnemyKey"));
	ACBoss* Boss = Cast<ACBoss>(AIC->GetBlackboardComponent()->GetValueAsObject("BossKey"));

	AIC->GetBlackboardComponent()->SetValueAsVector("PlayerLocation", Pet->GetOwner()->GetActorLocation());

	SetTarget(AIC, Pet, Enemy, Boss);

	if (Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.GetHit"))))
	{
		return;
	}

	if (AIC->GetBlackboardComponent()->GetValueAsObject("PlayerKey"))
	{
		if (AIC->GetBlackboardComponent()->GetValueAsObject("AttackTargetKey"))
		{
			float DistanceToEnemy = Pet->GetDistanceTo(Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject("AttackTargetKey")));

			if (DistanceToEnemy < 300.f)
			{
				if (Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.ChasingPlayer"))))
					Pet->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.ChasingPlayer")));
				if (Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Patrol"))))
					Pet->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Patrol")));
				if (Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Approach"))))
					Pet->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Approach")));
				if (!Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Attack"))))
					Pet->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Attack")));
				if (!Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Jump"))))
					Pet->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Jump")));
			}
			else if (DistanceToEnemy < 800.f)
			{
				if (Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.ChasingPlayer"))))
					Pet->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.ChasingPlayer")));
				if (Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Patrol"))))
					Pet->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Patrol")));
				if (Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Approach"))))
					Pet->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Approach")));
				if (!Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Jump"))))
					Pet->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Jump")));
				if (!Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Attack"))))
					Pet->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Attack")));
			}
			else
			{
				if (Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.ChasingPlayer"))))
					Pet->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.ChasingPlayer")));
				if (Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Patrol"))))
					Pet->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Patrol")));
				if (!Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Jump"))))
					Pet->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Jump")));
				if (Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Attack"))))
					Pet->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Attack")));
				if (!Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Approach"))))
					Pet->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Approach")));
			}
		}
		else
		{
			if (Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.ChasingPlayer"))))
				Pet->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.ChasingPlayer")));
			if (Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Approach"))))
				Pet->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Approach")));
			if (Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Attack"))))
				Pet->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Attack")));
			if (!Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Jump"))))
				Pet->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Jump")));
			if (!Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Patrol"))))
				Pet->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Patrol")));
		}
	}
	else
	{
		if (Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Patrol"))))
			Pet->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Patrol")));
		if (Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Approach"))))
			Pet->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Approach")));
		if (Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Attack"))))
			Pet->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Attack")));
		if (!Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Jump"))))
			Pet->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Jump")));
		if (!Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.ChasingPlayer"))))
			Pet->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag("AI.Action.ChasingPlayer"));
	}

}

void UCBTService_Pet::SetTarget(ACPetController* AIC, ACPet* Pet, ACEnemy* Enemy, ACBoss* Boss)
{
	float DistanceToEnemy = 0.0f;
	float DistanceToBoss = 0.0f;

	if (Enemy != nullptr && !(Enemy->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Dead")))))
	{
		DistanceToEnemy = Pet->GetDistanceTo(Enemy);
	}

	if (Boss != nullptr && !(Boss->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Dead")))))
	{
		DistanceToBoss = Pet->GetDistanceTo(Boss);
	}

	if (DistanceToEnemy >= DistanceToBoss)
	{
		AIC->GetBlackboardComponent()->SetValueAsObject("AttackTargetKey", Enemy);
	}
	else
	{
		AIC->GetBlackboardComponent()->SetValueAsObject("AttackTargetKey", Boss);
	}
}