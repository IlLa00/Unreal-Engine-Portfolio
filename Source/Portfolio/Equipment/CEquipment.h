#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataAsset/CWeaponDataAsset.h"
#include "CEquipment.generated.h"

class ACWeapon;

UCLASS()
class PORTFOLIO_API ACEquipment : public AActor
{
	GENERATED_BODY()

public:
	ACEquipment();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	void Equip(int32 slot);
	void Begin_Equip();
	void End_Equip();

public:
	UPROPERTY(EditDefaultsOnly, Category = "DataAsset")
		UCWeaponDataAsset* DataAsset;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
		TObjectPtr<UAnimMontage> Montage;

private:
	FWeaponData EquipWeapons[4]; // 캐릭터가 실제로 보유하고 있는 무기들

	ACharacter* OwnerCharacter;

	ACWeapon* EquipWeapon[4];
};
