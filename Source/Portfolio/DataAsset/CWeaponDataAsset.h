#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CWeaponDataAsset.generated.h"

class UImage;
class ACWeapon;

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<ACWeapon> WeaponClass; 

	UPROPERTY(EditAnywhere)
		FName WeaponName;

	UPROPERTY(EditAnywhere)
		UImage* WeaponImage;

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
	UPROPERTY(EditAnywhere, Category = "Weapon Data")
		TArray<FWeaponData> Datas;
};
