#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_Enemy.generated.h"

class ACEnemyController;
class ACEnemy;
class ACPlayer;
class ACPet;

UCLASS()
class PORTFOLIO_API UCBTService_Enemy : public UBTService
{
	GENERATED_BODY()
	
public:
	UCBTService_Enemy();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	void SetTarget(ACEnemyController* AIC, ACEnemy* Enemy, ACPlayer* Player, ACPet* Pet);
};
