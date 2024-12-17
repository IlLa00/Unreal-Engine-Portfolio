#pragma once

#include "CoreMinimal.h"
#include "Weapon/CWeapon.h"
#include "CHookGun.generated.h"

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
};
