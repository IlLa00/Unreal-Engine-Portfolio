#include "BTNode/CBTDecorator_TagCheck.h"
#include "Global.h"
#include "Interface/CAIInterface.h"
#include "AIController.h"

UCBTDecorator_TagCheck::UCBTDecorator_TagCheck()
{
	NodeName = "CheckTags";
}

bool UCBTDecorator_TagCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool Result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner()->GetPawn()->GetClass()->ImplementsInterface(UCAIInterface::StaticClass()))
	{
		ICAIInterface* AI = Cast<ICAIInterface>(OwnerComp.GetAIOwner()->GetPawn());
		CheckNullResult(AI, false);

		return AI->GetTagContainer().HasTag(GameplayTag);
	}

	return false;
}
