#pragma once

#include "CoreMinimal.h"
#include "Weapon/CWeapon.h"
#include "CRPG.generated.h"

class USplineComponent;
class ACRocket;

UCLASS()
class PORTFOLIO_API ACRPG : public ACWeapon
{
	GENERATED_BODY()
	
public:
	ACRPG();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void SphereTrace(FVector Location);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Component")
		USplineComponent* SplineComp;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Rocket")
		TSubclassOf<ACRocket> RocketClass;
};
