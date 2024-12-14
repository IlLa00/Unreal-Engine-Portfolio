#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_Boss.generated.h"

class ACEnemyController;
class ACBoss;
class ACPlayer;
class ACPet;

UCLASS()
class PORTFOLIO_API UCBTService_Boss : public UBTService
{
	GENERATED_BODY()
	
public:
	UCBTService_Boss();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	void SetTarget(ACEnemyController* AIC, ACBoss* Boss, ACPlayer* Player, ACPet* Pet);
};
