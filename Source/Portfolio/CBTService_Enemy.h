#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_Enemy.generated.h"


UCLASS()
class PORTFOLIO_API UCBTService_Enemy : public UBTService
{
	GENERATED_BODY()
	
public:
	UCBTService_Enemy();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
