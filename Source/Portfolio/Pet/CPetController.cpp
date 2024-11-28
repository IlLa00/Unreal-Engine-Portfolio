#include "CPetController.h"
#include "Global.h"
#include "BehaviorTree/BlackboardComponent.h"  
#include "BehaviorTree/BehaviorTree.h" 

ACPetController::ACPetController()
{
	CHelpers::GetAsset(&BBAsset, "/Game/BehaviorTree/BB_Pet");
	CheckNull(BBAsset);

	CHelpers::GetAsset(&BTAsset, "/Game/BehaviorTree/BT_Pet");
	CheckNull(BTAsset);
}

void ACPetController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BTAsset);
}

void ACPetController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ACPetController::OnUnPossess()
{
	Super::OnUnPossess();
}
