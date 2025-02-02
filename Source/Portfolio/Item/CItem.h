#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "../DataTable/CItemDataTable.h"
#include "CItem.generated.h"

class USkeletalMeshComponent;
class UBoxComponent;
class UNiagaraComponent;
class UCItemDataAsset;

UCLASS()
class PORTFOLIO_API ACItem : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	ACItem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual float GetValue() { return Value; }

protected:
	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Component")
		USkeletalMeshComponent* RootGravityComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
		UBoxComponent* BoxComp;

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
		TObjectPtr<UAbilitySystemComponent> ASC; // ¹öÇÁ ¾ø¾Ù²¨¸é ÀÌ°Íµµ ±»ÀÌ?


protected:
	UCItemDataAsset* DataAsset; // ÀÖ¾î¾ßµÊ?
	float Value; // ¹öÇÁ¾ø¾Ù²¨¸é ±»ÀÌ?

	UDataTable* DataTable;

	FItemDataTable Row;
};
