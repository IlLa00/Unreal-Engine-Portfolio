#pragma once

#include "CoreMinimal.h"
#include "Weapon/CWeapon.h"
#include "CRPG.generated.h"

class USplineComponent;
class ACRocket;
class UParticleSystem;

UCLASS()
class PORTFOLIO_API ACRPG : public ACWeapon
{
	GENERATED_BODY()
	
public:
	ACRPG();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
		void SphereTrace(FVector Location);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Component")
		USplineComponent* SplineComp;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Particle")
		UParticleSystem* ExplosionParticle;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Rocket")
		TSubclassOf<ACRocket> RocketClass;
};
