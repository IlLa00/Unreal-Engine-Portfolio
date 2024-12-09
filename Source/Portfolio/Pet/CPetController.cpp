#include "CPetController.h"
#include "Global.h"
#include "BehaviorTree/BlackboardComponent.h"  
#include "BehaviorTree/BehaviorTree.h" 
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Pet/CPet.h"
#include "Player/CPlayer.h"
#include "Enemy/CEnemy.h"

ACPetController::ACPetController()
{
	CHelpers::CreateActorComponent(this, &PerceptionComp, "PerceptionComp");
	CheckNull(PerceptionComp);

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	CheckNull(Sight);

	Sight->SightRadius = 600.f;
	Sight->LoseSightRadius = 800.f;
	Sight->PeripheralVisionAngleDegrees = 180.f;

	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;
	Sight->SetMaxAge(2.f);

	PerceptionComp->ConfigureSense(*Sight);

	TeamId = 0; // 플레이어랑 같은 소속
}

void ACPetController::BeginPlay()
{
	Super::BeginPlay();

}

void ACPetController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PrintLine();

	ACPet* PossessedPet = Cast<ACPet>(InPawn);
	CheckNull(PossessedPet);

	if (PossessedPet->GetBehaviorTree())
		RunBehaviorTree(PossessedPet->GetBehaviorTree());

	PerceptionComp->OnPerceptionUpdated.AddDynamic(this, &ACPetController::OnPerceptionUpdated);

	SetGenericTeamId(TeamId);
}

void ACPetController::OnUnPossess()
{
	Super::OnUnPossess();

	PerceptionComp->OnPerceptionUpdated.Clear();
}

void ACPetController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> PerceivedActors;

	PerceptionComp->GetCurrentlyPerceivedActors(nullptr, PerceivedActors);

	ACPet* Pet = Cast<ACPet>(GetPawn());
	CheckNull(Pet);

	ACPlayer* Player = nullptr;
	ACEnemy* Enemy = nullptr;

	for (const auto& Actor : PerceivedActors)
	{
		if (Cast<ACPlayer>(Actor))
		{
			Player = Cast<ACPlayer>(Actor);
			break;
		}

		if (Cast<ACEnemy>(Actor))
		{
			Enemy = Cast<ACEnemy>(Actor);
			break;
		}
	}

	if (GetBlackboardComponent())
	{
		GetBlackboardComponent()->SetValueAsObject("PlayerKey", Player);
		GetBlackboardComponent()->SetValueAsObject("EnemyKey", Enemy);
	}


}
