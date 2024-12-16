#include "CEquipment.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Weapon/CWeapon.h"

ACEquipment::ACEquipment()
{
	PrimaryActorTick.bCanEverTick = true;

	
}

void ACEquipment::BeginPlay()
{
	Super::BeginPlay();

	CheckNull(DataAsset);

	OwnerCharacter = Cast<ACPlayer>(GetOwner());
	CheckNull(OwnerCharacter);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = OwnerCharacter;

	// 스폰시키고 숨기고 필요할때만 보여주는 방식.
	if (DataAsset->Datas[0].WeaponClass)
	{
		EquipWeapon[0] = OwnerCharacter->GetWorld()->SpawnActor<ACWeapon>(DataAsset->Datas[0].WeaponClass, SpawnParams);
		CheckNull(EquipWeapon[0]);

		EquipWeapon[0]->SetActorHiddenInGame(true);
	}
	
	if (DataAsset->Datas[1].WeaponClass)
	{
		EquipWeapon[1] = OwnerCharacter->GetWorld()->SpawnActor<ACWeapon>(DataAsset->Datas[1].WeaponClass, SpawnParams);
		CheckNull(EquipWeapon[1]);

		EquipWeapon[1]->SetActorHiddenInGame(true);
	}

	if (DataAsset->Datas[2].WeaponClass)
	{
		EquipWeapon[2] = OwnerCharacter->GetWorld()->SpawnActor<ACWeapon>(DataAsset->Datas[2].WeaponClass, SpawnParams);
		CheckNull(EquipWeapon[2]);

		EquipWeapon[2]->SetActorHiddenInGame(true);
	}

	/*
	if (DataAsset->Datas[3].WeaponClass)
	{
		EquipWeapon[3] = OwnerCharacter->GetWorld()->SpawnActor<ACWeapon>(DataAsset->Datas[3].WeaponClass, SpawnParams);
		CheckNull(EquipWeapon[3]);

		EquipWeapon[3]->SetActorHiddenInGame(true);
	}*/
	
}

void ACEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACEquipment::Equip(int32 slot)
{
	CheckNull(EquipMontage);

	OwnerCharacter->PlayAnimMontage(EquipMontage);
	
	CurrentEquipWeapon = EquipWeapon[slot];
	// 위젯 변화
	// 무기 장착중인지 아닌지?

	if (CurrentEquipWeapon == EquipWeapon[slot])
	{
		PrintLine();
	}
}

void ACEquipment::Begin_Equip()
{ 
	// 무기 손 소켓에 붙이기
	CurrentEquipWeapon->SetActorHiddenInGame(false);

	CurrentEquipWeapon->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "hand_r_Weapon");

	// EquipWeapon[0]->GetD
	// 능력 장착

}

void ACEquipment::MainAction()
{
	// TryAbility~
}

