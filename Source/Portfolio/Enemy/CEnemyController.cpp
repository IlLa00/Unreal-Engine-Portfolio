#include "CEnemyController.h"
#include "Global.h"
#include "BehaviorTree/BlackboardComponent.h"  
#include "BehaviorTree/BehaviorTree.h" 

ACEnemyController::ACEnemyController()
{
	CHelpers::GetAsset(&BBAsset, "/Game/BehaviorTree/BB_Enemy");
	CheckNull(BBAsset);

	CHelpers::GetAsset(&BTAsset, "/Game/BehaviorTree/BT_Enemy");
	CheckNull(BTAsset);
}

void ACEnemyController::BeginPlay()
{
	Super::BeginPlay();
}

void ACEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	CLog::Print(InPawn->GetName());
}

void ACEnemyController::OnUnPossess()
{

}
