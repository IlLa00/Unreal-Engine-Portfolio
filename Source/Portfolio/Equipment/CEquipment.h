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
	void Equip(int32 slot);
	void Begin_Equip();

	void MainAction();

public:
	//UPROPERTY(EditDefaultsOnly, Category = "DataAsset")
	//	UCWeaponDataAsset* DataAsset; // 이게 여기있어야함?

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
		TObjectPtr<UAnimMontage> Montage;

private:
	ACPlayer* OwnerCharacter;
	ACWeapon* EquipWeapon[4]; // 이거 TArray써야할지도?
};
