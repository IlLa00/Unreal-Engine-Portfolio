#include "CEnemyController.h"
#include "Global.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Player/CPlayer.h"
#include "Enemy/CEnemy.h"

ACEnemyController::ACEnemyController()
{
	CHelpers::CreateActorComponent(this, &PerceptionComp, "PerceptionComp");
	CheckNull(PerceptionComp);

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	CheckNull(Sight);

	Sight->SightRadius = 600.f;
	Sight->LoseSightRadius = 800.f;
	Sight->PeripheralVisionAngleDegrees = 90.f;

	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;
	Sight->SetMaxAge(2.f);

	PerceptionComp->ConfigureSense(*Sight);

	TeamId = 1;
}

void ACEnemyController::BeginPlay()
{
	Super::BeginPlay();

}

void ACEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ACEnemy* PossesEnemy = Cast<ACEnemy>(InPawn);
	CheckNull(PossesEnemy);

	if (PossesEnemy->GetBehaviorTree())
		RunBehaviorTree(PossesEnemy->GetBehaviorTree());
	
	PerceptionComp->OnPerceptionUpdated.AddDynamic(this, &ACEnemyController::OnPerceptionUpdated);
	SetGenericTeamId(TeamId);

}

void ACEnemyController::OnUnPossess()
{
	Super::OnUnPossess();

	PerceptionComp->OnPerceptionUpdated.Clear();
}

void ACEnemyController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> PerceivedActors;

	PerceptionComp->GetCurrentlyPerceivedActors(nullptr, PerceivedActors);

	ACPlayer* Player = nullptr;

	for (const auto& Actor : PerceivedActors)
	{
		Player = Cast<ACPlayer>(Actor);

		if (Player)
		{
			if (GetBlackboardComponent())
			{
				GetBlackboardComponent()->SetValueAsObject("PlayerKey", Player); // 지금 블랙보드가 없음
				break;
			}
			PrintLine();
		}
	}
}

