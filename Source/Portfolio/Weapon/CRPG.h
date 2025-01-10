#pragma once

#include "CoreMinimal.h"
#include "Weapon/CWeapon.h"
#include "CRPG.generated.h"

UCLASS()
class PORTFOLIO_API ACRPG : public ACWeapon
{
	GENERATED_BODY()
	
public:
	ACRPG();

protected:
	virtual void BeginPlay() override;
};
