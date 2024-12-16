#pragma once

#include "CoreMinimal.h"
#include "Weapon/CWeapon.h"
#include "CSword.generated.h"

UCLASS()
class PORTFOLIO_API ACSword : public ACWeapon
{
	GENERATED_BODY()
	
public:
	ACSword();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
