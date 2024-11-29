#pragma once

#include "CoreMinimal.h"
#include "CWeapon.h"
#include "CAxe.generated.h"

UCLASS()
class PORTFOLIO_API ACAxe : public ACWeapon
{
	GENERATED_BODY()
	
public:	
	ACAxe();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};
