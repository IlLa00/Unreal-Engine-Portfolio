#include "CBTService_Enemy.h"
#include "Global.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Enemy/CEnemyController.h"

UCBTService_Enemy::UCBTService_Enemy()
{
	NodeName = "RootService";
}


void UCBTService_Enemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
	CheckNull(AIC);

	
}
