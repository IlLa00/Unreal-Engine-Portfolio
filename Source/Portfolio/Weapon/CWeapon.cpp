#include "CWeapon.h"
#include "Global.h"

ACWeapon::ACWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::GetAsset(&DataAsset, "'/Game/DataAsset/DA_Weapon");
	CheckNull(DataAsset);
}

void ACWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

