#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataAsset/CWeaponDataAsset.h"
#include "CEquipment.generated.h"

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

private:
	UCWeaponDataAsset* DataAsset;
	FWeaponData EquipWeapons[4];

	// 위젯을 가짐 - 현재 무슨 장비를 끼고있는지/
};
