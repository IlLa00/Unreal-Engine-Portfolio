#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CEnemyController.generated.h"

class UBlackboardData;
class UBehaviorTree;

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

public:
	UPROPERTY(EditDefaultsOnly, Category = "BlackBoard")
		UBlackboardData* BBAsset;

	UPROPERTY(EditDefaultsOnly, Category = "Behavior Tree")
		UBehaviorTree* BTAsset;

};
