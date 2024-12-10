#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_SetSpeed.generated.h"

UCLASS()
class PORTFOLIO_API UCBTTaskNode_SetSpeed : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCBTTaskNode_SetSpeed();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
protected:
	UPROPERTY(EditInstanceOnly, Category = "Speed Value")
		float Speed;
};
