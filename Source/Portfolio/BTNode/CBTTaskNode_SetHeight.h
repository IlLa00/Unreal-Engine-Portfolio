#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_SetHeight.generated.h"

UCLASS()
class PORTFOLIO_API UCBTTaskNode_SetHeight : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UCBTTaskNode_SetHeight();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Value")
		bool IsFly;
};
