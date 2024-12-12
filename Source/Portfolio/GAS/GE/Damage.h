#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Damage.generated.h"

UCLASS()
class PORTFOLIO_API UDamage : public UGameplayEffect
{
	GENERATED_BODY()
	
public:
	UDamage();

public:
	void SetModify(AActor* OwnerActor, AActor* OtherActor);

};
