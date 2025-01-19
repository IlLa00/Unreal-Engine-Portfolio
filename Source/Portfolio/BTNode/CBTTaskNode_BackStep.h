#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_BackStep.generated.h"

class UAnimMontage;

UCLASS()
class PORTFOLIO_API UCBTTaskNode_BackStep : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCBTTaskNode_BackStep();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
private:
	UAnimMontage* BackStepMontage;
};
