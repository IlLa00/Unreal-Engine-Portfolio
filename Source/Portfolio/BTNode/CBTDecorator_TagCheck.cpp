#include "BTNode/CBTDecorator_TagCheck.h"
#include "Global.h"
#include "Enemy/CEnemyController.h"
#include "Enemy/CEnemy.h"
#include "Pet/CPetController.h"
#include "Pet/CPet.h"
#include "BehaviorTree/BehaviorTree.h"

UCBTDecorator_TagCheck::UCBTDecorator_TagCheck()
{
	NodeName = "CheckTags";
}

bool UCBTDecorator_TagCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	if (OwnerComp.GetRootTree()->GetName() == FName("BT_Enemy").ToString())
	{
		ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
		CheckNullResult(AIC, false);

		ACEnemy* Enemy = Cast<ACEnemy>(AIC->GetPawn());
		CheckNullResult(Enemy, false);

		return Enemy->GetTagContainer().HasTag(GameplayTag);
	}
	else if (OwnerComp.GetRootTree()->GetName() == FName("BT_Pet").ToString())
	{
		ACPetController* AIC = Cast<ACPetController>(OwnerComp.GetAIOwner());
		CheckNullResult(AIC, false);

		ACPet* Pet = Cast<ACPet>(AIC->GetPawn());
		CheckNullResult(Pet, false);

		return Pet->GetTagContainer().HasTag(GameplayTag);
	}

	return false;
}
