#pragma once

#include "CoreMinimal.h"
#include "Weapon/CWeapon.h"
#include "CHookGun.generated.h"

class UCableComponent;
class USplineComponent;

UCLASS()
class PORTFOLIO_API ACHookGun : public ACWeapon
{
	GENERATED_BODY()
	
public:
	ACHookGun();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE virtual UCableComponent* GetCableComp() { return CableComp; }
	FORCEINLINE virtual USplineComponent* GetSplineComp() { return SplineComp; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Component")
		UCableComponent* CableComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
		USplineComponent* SplineComp;
};
