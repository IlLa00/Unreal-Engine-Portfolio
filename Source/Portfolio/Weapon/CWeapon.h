#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
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
	virtual FGameplayTag* GetTag() { return &Tag; }
	virtual FName GetSocketName() { return AttachSocketName; }
	virtual FGameplayAbilitySpec GetWeaponAbilitySpec() { return WeaponAbilitySpec;}

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Component")
		USceneComponent* RootComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
		UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName AttachSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
		TObjectPtr<UAbilitySystemComponent> ASC;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
		TObjectPtr<UCWeaponAttributeSet> Attribute;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
		FGameplayTag Tag;

protected:
	UCWeaponDataAsset* DataAsset;
	FGameplayAbilitySpec WeaponAbilitySpec;
};
