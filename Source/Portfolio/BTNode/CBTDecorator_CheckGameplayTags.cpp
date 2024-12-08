#include "CBTDecorator_CheckGameplayTags.h"
#include "Global.h"
#include "Enemy/CEnemyController.h"
#include "Enemy/CEnemy.h"

UCBTDecorator_CheckGameplayTags::UCBTDecorator_CheckGameplayTags()
{
    TagsToMatch = EGameplayContainerMatchType::Any;

	NodeName = "CheckTag";
}

bool UCBTDecorator_CheckGameplayTags::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
	CheckNullResult(AIC, false);

	ACEnemy* Enemy = Cast<ACEnemy>(AIC->GetPawn());
	CheckNullResult(Enemy, false);

	return Enemy->GetTagContainer().HasAny(GameplayTags);
}
