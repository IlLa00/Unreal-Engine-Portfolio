#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "CBTTask_MoveToActor.generated.h"

UCLASS()
class PORTFOLIO_API UCBTTask_MoveToActor : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UCBTTask_MoveToActor();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
