#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Interface/CAttackCompInterface.h"
#include "GameplayTagContainer.h"
#include "CWeapon.generated.h"

class UAttributeSet;
class UCWeaponAttributeSet;
class UCWeaponDataAsset;
class UTexture;
class UBoxComponent;
class UGameplayEffect;

UCLASS()
class PORTFOLIO_API ACWeapon : public AActor, public IAbilitySystemInterface, public ICAttackCompInterface
{
	GENERATED_BODY()
	
public:	
	ACWeapon();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UCWeaponAttributeSet* GetAttiribute() { return Attribute; }
	virtual FGameplayTag* GetTag() { return &Tag; }
	virtual FName GetSocketName() { return AttachSocketName; }
	virtual FGameplayAbilitySpec GetWeaponAbilitySpec() { return WeaponAbilitySpec;}
	virtual FGameplayAbilitySpec GetWeaponSubAbilitySpec() { return WeaponSubAbilitySpec; }
	virtual UCWeaponDataAsset* GetDataAsset() { return DataAsset; }
	virtual UTexture* GetWeaponImage() { return WeaponImage; }
	virtual FText GetWeaponName() { return WeaponName; }

	virtual UBoxComponent* GetAttackComp() override { return AttackCollisionComp; }

	virtual void OnDamageBuff();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Component")
		USceneComponent* RootComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
		UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
		UBoxComponent* AttackCollisionComp;

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName AttachSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
		TObjectPtr<UAbilitySystemComponent> ASC;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
		TObjectPtr<UCWeaponAttributeSet> Attribute;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
		FGameplayTag Tag;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
		TSubclassOf<UGameplayEffect> BPDamageBuffEffect;

protected:
	UCWeaponDataAsset* DataAsset;
	FGameplayAbilitySpec WeaponAbilitySpec;
	FGameplayAbilitySpec WeaponSubAbilitySpec;

	UTexture* WeaponImage;
	FText WeaponName;
	float Proficiency;

	FGameplayEffectSpecHandle DamageBuffEffectHandle;
};
