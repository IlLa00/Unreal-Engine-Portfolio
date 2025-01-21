#pragma once

#include "CoreMinimal.h"
#include "Item/CItem.h"
#include "CItem_Test.generated.h"

class UDataTable;

UCLASS()
class PORTFOLIO_API ACItem_Test : public ACItem
{
	GENERATED_BODY()
	
public:
	ACItem_Test();

public:
	void BeginPlay() override;

protected:
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	UDataTable* DataTable;
};
