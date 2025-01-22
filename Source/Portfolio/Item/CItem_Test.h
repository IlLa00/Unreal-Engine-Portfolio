#pragma once

#include "CoreMinimal.h"
#include "Item/CItem.h"
#include "CItem_Test.generated.h"

class UDataTable;
class UTexture;

UCLASS()
class PORTFOLIO_API ACItem_Test : public ACItem
{
	GENERATED_BODY()
	
public:
	ACItem_Test();

public:
	void BeginPlay() override;

	FORCEINLINE FName GetItemName() { return ItemName; }
	FORCEINLINE UTexture* GetItemTexture() { return ItemTexture; }
	FORCEINLINE int32 GetCount() { return Count; }

	void IncreaseCount();

protected:
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	UDataTable* DataTable;
	FName ItemName;
	UTexture* ItemTexture;

	int32 Count;
};
