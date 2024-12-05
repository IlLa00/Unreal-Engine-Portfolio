#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CEnemyController.generated.h"

class UBlackboardData;
class UBehaviorTree;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class PORTFOLIO_API ACEnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
	ACEnemyController();

public:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

public:
	UPROPERTY(EditDefaultsOnly, Category = "Component")
		UAIPerceptionComponent* PerceptionComp;

private:
	UAISenseConfig_Sight* Sight;

};
