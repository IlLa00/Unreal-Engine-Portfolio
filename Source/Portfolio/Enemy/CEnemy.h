#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CEnemy.generated.h"

class UBehaviorTree;

UCLASS()
class PORTFOLIO_API ACEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	ACEnemy();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UBehaviorTree* GetBehaviorTree() { return BT; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Behavior Tree")
		UBehaviorTree* BT;
};
