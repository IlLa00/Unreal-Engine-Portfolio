#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_Attack.generated.h"

UCLASS()
class PORTFOLIO_API UCBTTaskNode_Attack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UCBTTaskNode_Attack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
