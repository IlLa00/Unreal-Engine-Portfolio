#include "CEnemyController.h"
#include "Global.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Player/CPlayer.h"
#include "Enemy/CEnemy.h"
#include "Enemy/CMonster.h"
#include "Enemy/CBoss.h"
#include "Pet/CPet.h"

ACEnemyController::ACEnemyController()
{
	CHelpers::CreateActorComponent(this, &PerceptionComp, "PerceptionComp");
	CheckNull(PerceptionComp);

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	CheckNull(Sight);

	Hear = CreateDefaultSubobject<UAISenseConfig_Hearing>("Hear");
	CheckNull(Hear);

	Sight->SightRadius = 600.f;
	Sight->LoseSightRadius = 800.f;
	Sight->PeripheralVisionAngleDegrees = 90.f;

	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;
	Sight->SetMaxAge(2.f);

	Hear->HearingRange = 800.f;
	Hear->bUseLoSHearing = true;
	Hear->LoSHearingRange = 1000.f;
	Hear->DetectionByAffiliation.bDetectEnemies = true;
	Hear->DetectionByAffiliation.bDetectFriendlies = true;
	Hear->DetectionByAffiliation.bDetectNeutrals = true;
	Hear->SetMaxAge(10.f);

	PerceptionComp->ConfigureSense(*Sight);
	PerceptionComp->ConfigureSense(*Hear);

	TeamId = 1;
}

void ACEnemyController::BeginPlay()
{
	Super::BeginPlay();

}

void ACEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn->IsA<ACMonster>())
	{
		ACMonster* PossesMonster = Cast<ACMonster>(InPawn);
		CheckNull(PossesMonster);

		if (PossesMonster->GetBehaviorTree())
			RunBehaviorTree(PossesMonster->GetBehaviorTree());

	}
	else if (InPawn->IsA<ACBoss>())
	{
		ACBoss* PossesBoss = Cast<ACBoss>(InPawn);
		CheckNull(PossesBoss);

		if (PossesBoss->GetBehaviorTree())
			RunBehaviorTree(PossesBoss->GetBehaviorTree());

		Sight->SightRadius = 2000.f;
		Sight->LoseSightRadius = 2500.f;
		Sight->PeripheralVisionAngleDegrees = 180.f; // z축이 너무 차이가 나서 시야감지가 안됨..

		Hear->HearingRange = 8000.f;
		Hear->LoSHearingRange = 10000.f; // 얘는 z축이 괜찮네?
	}

	PerceptionComp->OnPerceptionUpdated.AddDynamic(this, &ACEnemyController::OnPerceptionUpdated);
	SetGenericTeamId(TeamId);

}

void ACEnemyController::OnUnPossess()
{
	Super::OnUnPossess();

	PerceptionComp->OnPerceptionUpdated.Clear();
	Destroy();
}

void ACEnemyController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> PerceivedActors;
	PerceptionComp->GetCurrentlyPerceivedActors(nullptr, PerceivedActors);

	ACEnemy* Enemy = Cast<ACEnemy>(GetPawn());
	CheckNull(Enemy);

	ACPlayer* Player = nullptr;
	ACPet* Pet = nullptr;

	for (const auto& Actor : PerceivedActors)
	{
		if (Actor->IsA<ACPet>())
		{
			Pet = Cast<ACPet>(Actor);
		}
		if (Actor->IsA<ACPlayer>())
		{
			Player = Cast<ACPlayer>(Actor);
		}
	}

	if (GetBlackboardComponent())
	{
		GetBlackboardComponent()->SetValueAsObject("PlayerKey", Player);
		GetBlackboardComponent()->SetValueAsObject("PetKey", Pet);
	}

}

