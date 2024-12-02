#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilitySystemComponent.h"
#include "Weapon/CWeapon.h"
#include "CWeaponDataAsset.generated.h"


USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<ACWeapon> WeaponClass; // 무기 클래스

	UPROPERTY(EditAnywhere)
		TSubclassOf<UAttributeSet> AttributeClass; // 무기의 데미지 및 숙련도 

	UPROPERTY(EditAnywhere)
		TSubclassOf<UGameplayAbility> AbilityClass; // 무기의 능력 <- 여기서 에임기능 , 근데 이거 오픈해야됨?

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
