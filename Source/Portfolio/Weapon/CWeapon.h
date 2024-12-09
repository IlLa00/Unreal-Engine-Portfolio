#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "CWeapon.generated.h"

class UAttributeSet;
class UCWeaponAttributeSet;
class UCWeaponDataAsset;

UCLASS()
class PORTFOLIO_API ACWeapon : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	ACWeapon();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UCWeaponAttributeSet* GetAttiribute() { return Attribute; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Component")
		USceneComponent* RootComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
		UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
		TObjectPtr<UAbilitySystemComponent> ASC;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
		TObjectPtr<UCWeaponAttributeSet> Attribute;

protected:
	UCWeaponDataAsset* DataAsset;
};
