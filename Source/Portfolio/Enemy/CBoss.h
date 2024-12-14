#pragma once

#include "CoreMinimal.h"
#include "Enemy/CEnemy.h"
#include "CBoss.generated.h"

class UFloatingPawnMovement;

UCLASS()
class PORTFOLIO_API ACBoss : public ACEnemy
{
	GENERATED_BODY()
	

public:
	ACBoss();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE UFloatingPawnMovement* GetFloatingComp() { return FloatingComp; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AnimClass")
		TSubclassOf<UAnimInstance> AnimClass;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
		UFloatingPawnMovement* FloatingComp;
};
