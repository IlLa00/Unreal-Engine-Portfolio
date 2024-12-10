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
#include "BTNode/CBlackboardKeyType_ObjectArray.h"

ACPetController::ACPetController()
{
	CHelpers::CreateActorComponent(this, &PerceptionComp, "PerceptionComp");
	CheckNull(PerceptionComp);

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	CheckNull(Sight);

	Sight->SightRadius = 1000.f;
	Sight->LoseSightRadius = 1200.f;
	Sight->PeripheralVisionAngleDegrees = 180.f;

	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;
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

	ACPet* PossessedPet = Cast<ACPet>(InPawn);
	CheckNull(PossessedPet);

	if (PossessedPet->GetBehaviorTree())
		RunBehaviorTree(PossessedPet->GetBehaviorTree());

	PossessedPet->SetOwner(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

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
		if (Actor->IsA<ACEnemy>())
		{
			Enemy = Cast<ACEnemy>(Actor); // 나중에 여기서 우선순위 같은거 매겨보자
		}
		if (Actor->IsA<ACPlayer>())
		{
			Player = Cast<ACPlayer>(Actor);
		}
	}

	if (GetBlackboardComponent())
	{
		GetBlackboardComponent()->SetValueAsObject("PlayerKey", Player);
		GetBlackboardComponent()->SetValueAsObject("EnemyKey", Enemy);
	}
}