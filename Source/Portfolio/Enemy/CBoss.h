#pragma once

#include "CoreMinimal.h"
#include "Enemy/CEnemy.h"
#include "CBoss.generated.h"

UCLASS()
class PORTFOLIO_API ACBoss : public ACEnemy
{
	GENERATED_BODY()
	
public:
	ACBoss();

public:
	UPROPERTY(EditDefaultsOnly, Category = "AnimClass")
		TSubclassOf<UAnimInstance> AnimClass;
};
