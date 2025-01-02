#include "CBTService_Pet.h"
#include "Global.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Pet/CPetController.h"
#include "Pet/CPet.h"
#include "Enemy/CEnemy.h"
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

	AIC->GetBlackboardComponent()->SetValueAsVector("PlayerLocation", Pet->GetOwner()->GetActorLocation()); 

	if (Player)
	{
		if (Enemy)
		{
			float DistanceToEnemy = Pet->GetDistanceTo(Enemy);

			if (DistanceToEnemy < 500.f)
			{
				Pet->GetTagContainer().Reset();
				Pet->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Attack")));
			}
			else
			{
				Pet->GetTagContainer().Reset();
				Pet->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Approach")));
			}
		}
		else
		{
			Pet->GetTagContainer().Reset();
			Pet->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag("AI.Action.Patrol"));
		}
	}
	else
	{
		Pet->GetTagContainer().Reset();
		Pet->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag("AI.Action.ChasingPlayer"));
	}

}
