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

	AIC->GetBlackboardComponent()->SetValueAsVector("PlayerLocation", Pet->GetOwner()->GetActorLocation()); // 이거 안되고있음 오너인식안되는듯

	CLog::Print(Pet->GetOwner()->GetName()); // 왜 컨트롤러가나옴?

	/*
	1. 플레이어와 멀어지면 = 플레이어 근처로 다가오게 ( 워크스피드 높이자 )
	2. 플레이어 근처이고 + 주변에 몬스터가 없으면 = 순찰 (EQS)
	3. 플레이어 근처이고 + 주변에 몬스터가 있고 + 공격범위 밖이면 = 접근
	4. 플레이어 근처이고 + 주변에 몬스터가 있고 + 공격범위 안이면 = 공격
	*/


	if (Player)
	{
		if (Enemy)
		{
			float DistanceToEnemy = Pet->GetDistanceTo(Enemy);

			if (DistanceToEnemy < 150.f)
			{
				Pet->GetTagContainer().Reset();
				Pet->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag(FName("Pet.State.Attack")));
			}
			Pet->GetTagContainer().Reset();
			Pet->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag(FName("Pet.State.Approach")));
		}
		Pet->GetTagContainer().Reset();
		Pet->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag("Pet.State.Patrol"));
	}

	Pet->GetTagContainer().Reset();
	Pet->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag("Pet.State.ChasingPlayer"));

}
