#pragma once

#include "CoreMinimal.h"
#include "Item/CItem.h"
#include "CItem_HealBuff.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class PORTFOLIO_API ACItem_HealBuff : public ACItem
{
	GENERATED_BODY()
	
public:
	ACItem_HealBuff();

protected:
	void BeginPlay() override;

protected:
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Niagara")
		UNiagaraComponent* NiagaraComp;

	UPROPERTY(EditDefaultsOnly, Category = "Niagara")
		UNiagaraSystem* OverlapParitcle;
};
