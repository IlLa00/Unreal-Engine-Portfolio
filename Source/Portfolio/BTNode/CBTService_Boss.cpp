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

	SetTarget(AIC, Boss, Player, Pet);

	if (AIC->GetBlackboardComponent()->GetValueAsObject("AttackTargetKey")) // 타깃이 감지되면
	{
		Boss->SetWidget(true);

		FHitResult HitResult;

		if (GetWorld()->SweepSingleByChannel(HitResult,Boss->GetActorLocation(), Boss->GetActorLocation()+FVector(1), FQuat::Identity,ECollisionChannel::ECC_Pawn,FCollisionShape::MakeSphere(1500.f)))
		{
			if (Boss->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Patrol"))))
				Boss->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Patrol")));
			if (Boss->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Approach"))))
				Boss->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Approach")));
			if (!Boss->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Attack"))))
				Boss->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Attack")));
		}
		else
		{
			if (Boss->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Patrol"))))
				Boss->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Patrol")));
			if (Boss->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Attack"))))
				Boss->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Attack")));
			if (!Boss->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Approach"))))
				Boss->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Approach")));
		}
	}
	else
	{
		Boss->SetWidget(false); // 여기 자꾸 왜 이러지

		if(Boss->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Approach"))))
			Boss->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Approach")));
		if (Boss->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Attack"))))
			Boss->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Attack")));
		if (!Boss->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Patrol"))))
			Boss->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Patrol")));
	}
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