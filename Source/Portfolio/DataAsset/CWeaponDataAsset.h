#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilitySystemComponent.h"
#include "../Weapon/CWeapon.h"
#include "CWeaponDataAsset.generated.h"


USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<ACWeapon> WeaponClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UAttributeSet> AttributeClass;

	UPROPERTY(EditAnywhere)
		float BaseDamage;

	UPROPERTY(EditAnywhere)
		float BaseProficiency;

};

UCLASS()
class PORTFOLIO_API UCWeaponDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UCWeaponDataAsset();

public:
	UPROPERTY(EditAnywhere, Category = "Weapon Data")
		TArray<FWeaponData> Datas;
};
