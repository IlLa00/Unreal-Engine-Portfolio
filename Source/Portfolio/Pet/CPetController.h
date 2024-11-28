#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CPetController.generated.h"

class UBlackboardData;
class UBehaviorTree;

UCLASS()
class PORTFOLIO_API ACPetController : public AAIController
{
	GENERATED_BODY()
	
public:
	ACPetController();

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
