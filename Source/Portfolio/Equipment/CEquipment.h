#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataAsset/CWeaponDataAsset.h"
#include "CEquipment.generated.h"

class ACWeapon;
class ACPlayer;

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
	FORCEINLINE ACWeapon* GetCurrentCurrentEquipWeapon() { return CurrentEquipWeapon; }
	FORCEINLINE ACWeapon** GetEquipWeapons() { return EquipWeapon; }

public:
	void Equip(int32 slot);
	void Begin_Equip();

	void OnMainAction();
	void OffMainAction();

	void OnSubAction();
	void OffSubAction();

	void Reload();

	void Test2();

public:
	UPROPERTY(EditDefaultsOnly, Category = "DataAsset")
		UCWeaponDataAsset* DataAsset; // 이게 여기있어야함?

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
		TObjectPtr<UAnimMontage> EquipMontage;

private:
	ACPlayer* OwnerCharacter;
	ACWeapon* EquipWeapon[4];

	ACWeapon* CurrentEquipWeapon;
	ACWeapon* NewWeapon;
};
