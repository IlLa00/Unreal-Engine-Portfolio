#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "CBTTask_MoveTo.generated.h"

UCLASS()
class PORTFOLIO_API UCBTTask_MoveTo : public UBTTask_MoveTo
{
	GENERATED_BODY()
	
public:
	UCBTTask_MoveTo();

protected:
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
