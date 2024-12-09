#include "BTNode/CBTDecorator_TagCheck.h"
#include "Global.h"
#include "Enemy/CEnemyController.h"
#include "Enemy/CEnemy.h"
#include "Pet/CPetController.h"
#include "Pet/CPet.h"

UCBTDecorator_TagCheck::UCBTDecorator_TagCheck()
{
	NodeName = "CheckTags";
}

bool UCBTDecorator_TagCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	// OwnerComp.GetOwner()

	ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
	CheckNullResult(AIC, false);

	ACEnemy* Enemy = Cast<ACEnemy>(AIC->GetPawn());
	CheckNullResult(Enemy, false);

	return Enemy->GetTagContainer().HasTag(GameplayTag);
}
