#include "CEquipment.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Weapon/CWeapon.h"
#include "Weapon/CRifle.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "Widget/CPlayerWidget.h"
#include "DataAsset/CWeaponDataAsset.h"
#include "GAS/GA/ReloadRifle.h"
#include "GAS/GA/Aim.h"
#include "GAS/Attribute/CWeaponAttributeSet.h"

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

	if (DataAsset->Datas[3].WeaponClass)
	{
		EquipWeapon[3] = OwnerCharacter->GetWorld()->SpawnActor<ACWeapon>(DataAsset->Datas[3].WeaponClass, SpawnParams);
		CheckNull(EquipWeapon[3]);

		EquipWeapon[3]->SetActorHiddenInGame(true);
	}

}

void ACEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACEquipment::Equip(int32 slot)
{
	CheckNull(EquipMontage);

	if (CurrentEquipWeapon && CurrentEquipWeapon->IsA<ACRifle>())
	{
		CurrentEquipWeapon->GetAbilitySystemComponent()->CancelAbility(CurrentEquipWeapon->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAim::StaticClass())->Ability);
	}

	OwnerCharacter->PlayAnimMontage(EquipMontage);

	NewWeapon = EquipWeapon[slot - 1];

	if (NewWeapon == CurrentEquipWeapon)
	{
		OwnerCharacter->GetPlayerWidget()->UpdateEquipWeaponImage(nullptr);
		OwnerCharacter->GetPlayerWidget()->UpdateEquipWeaponName(FText());
		OwnerCharacter->GetPlayerWidget()->UpdateEquipWeaponProficiency(0.f);
		OwnerCharacter->GetPlayerWidget()->ShowCurrentBullet(false);
		return;
	}
	else
	{
		OwnerCharacter->GetPlayerWidget()->UpdateEquipWeaponImage(NewWeapon->GetWeaponImage());
		OwnerCharacter->GetPlayerWidget()->UpdateEquipWeaponName(NewWeapon->GetWeaponName());
		OwnerCharacter->GetPlayerWidget()->UpdateEquipWeaponProficiency(NewWeapon->GetAttiribute()->GetCurrentProficiency());
	}

	if (NewWeapon->IsA<ACRifle>())
	{
		ACRifle* Rifle = Cast<ACRifle>(NewWeapon);
		CheckNull(Rifle);

		OwnerCharacter->GetPlayerWidget()->ShowCurrentBullet(true);
		OwnerCharacter->GetPlayerWidget()->UpdateBaseBullet(Rifle->GetBaseBullet());
		OwnerCharacter->GetPlayerWidget()->UpdateCurrentBullet(Rifle->GetCurrentBullet());
	}
	else
		OwnerCharacter->GetPlayerWidget()->ShowCurrentBullet(false);

	// 우클릭 풀어야됨
	// todo.. 현재 장비해제하면 위젯도 아무것도 없게 만들어야함
}

void ACEquipment::Begin_Equip()
{
	CheckNull(NewWeapon);

	if (CurrentEquipWeapon)
	{
		CurrentEquipWeapon->SetActorHiddenInGame(true);
		CurrentEquipWeapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		OwnerCharacter->GetTagContainer().RemoveTag(*(CurrentEquipWeapon->GetTag()));

		if (CurrentEquipWeapon == NewWeapon)
		{
			CurrentEquipWeapon = nullptr;
			return;
		}

		CurrentEquipWeapon = nullptr;

	}

	NewWeapon->SetActorHiddenInGame(false);
	NewWeapon->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, NewWeapon->GetSocketName());

	OwnerCharacter->GetTagContainer().AddTag(*(NewWeapon->GetTag()));

	CurrentEquipWeapon = NewWeapon;
}

void ACEquipment::OnMainAction()
{
	CheckNull(CurrentEquipWeapon);

	CurrentEquipWeapon->GetAbilitySystemComponent()->TryActivateAbility(CurrentEquipWeapon->GetWeaponAbilitySpec().Handle);

	// todo.. 총제외 스테미너 감소
}

void ACEquipment::OffMainAction()
{
	CheckNull(CurrentEquipWeapon); 

	CurrentEquipWeapon->GetAbilitySystemComponent()->CancelAbilityHandle(CurrentEquipWeapon->GetWeaponAbilitySpec().Handle);
}



void ACEquipment::OnSubAction()
{
	CheckNull(CurrentEquipWeapon);

	CurrentEquipWeapon->GetAbilitySystemComponent()->TryActivateAbility(CurrentEquipWeapon->GetWeaponSubAbilitySpec().Handle);

}

void ACEquipment::OffSubAction()
{
	CheckNull(CurrentEquipWeapon);
	
	// todo.. 여기 서브능력 진행중인지 아닌지 검사하는 조건 추가해야할듯
	CurrentEquipWeapon->GetAbilitySystemComponent()->CancelAbilityHandle(CurrentEquipWeapon->GetWeaponSubAbilitySpec().Handle);
}

void ACEquipment::Reload()
{
	CheckNull(CurrentEquipWeapon);

	if (CurrentEquipWeapon->GetWeaponName().ToString() == "Rifle")
	{
		CurrentEquipWeapon->GetAbilitySystemComponent()->TryActivateAbility(CurrentEquipWeapon->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UReloadRifle::StaticClass())->Handle);
	}
}