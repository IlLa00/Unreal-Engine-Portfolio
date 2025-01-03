#include "CRifle.h"
#include "Global.h"
#include "AbilitySystemComponent.h"
#include "DataAsset/CWeaponDataAsset.h"
#include "GAS/Attribute/CWeaponAttributeSet.h"
#include "GAS/GA/Rifle.h"
#include "GAS/GA/Aim.h"
#include "GAS/GA/ReloadRifle.h"
#include "Player/CPlayer.h"
#include "Widget/CPlayerWidget.h"

ACRifle::ACRifle()
{
	PrimaryActorTick.bCanEverTick = true;

	UStaticMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Assets/Weapon/lowpolyRifle");
	CheckNull(MeshAsset);

	MeshComp->SetStaticMesh(MeshAsset);
	MeshComp->SetRelativeScale3D(FVector(0.2));

	AttachSocketName = "hand_r_Rifle";

	BaseBullet = 30;

}

void ACRifle::BeginPlay()
{
	Super::BeginPlay();

	CheckNull(ASC);
	CheckNull(Attribute);

	if (ASC)
	{
		FGameplayAbilitySpec AbilitySpec(URifle::StaticClass());
		WeaponAbilitySpec = AbilitySpec;
		ASC->GiveAbility(AbilitySpec);

		FGameplayAbilitySpec SubAbilitySpec(UAim::StaticClass());
		WeaponSubAbilitySpec = SubAbilitySpec;
		ASC->GiveAbility(SubAbilitySpec);

		FGameplayAbilitySpec ReloadAbilitySpec(UReloadRifle::StaticClass());
		ASC->GiveAbility(ReloadAbilitySpec);

	}

	for (const auto& data : DataAsset->Datas)
	{
		if (GetClass() == data.WeaponClass)
		{
			Attribute->SetBaseDamage(data.BaseDamage);
			Attribute->SetBaseProficiency(data.BaseProficiency);

			Attribute->SetCurrentDamage(Attribute->GetBaseDamage());
			Attribute->SetCurrentProficiency(0.f);

			if (data.WeaponImage)
				WeaponImage = data.WeaponImage;

			if (data.WeaponName != NAME_None)
				WeaponName = FText::FromString(data.WeaponName.ToString());
			break;
		}
	}

	CurrentBullet = BaseBullet;
}

void ACRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACRifle::Reload()
{
	CurrentBullet = BaseBullet;

	ACPlayer* Player = Cast<ACPlayer>(GetOwner());
	CheckNull(Player);

	Player->GetPlayerWidget()->UpdateCurrentBullet(CurrentBullet);
}

void ACRifle::Shooting_Implementation()
{
	if (IsReload())
		return;

	if (CurrentBullet <= 0)
	{
		bReload = true;
		Reloading();
		return;
	}

	CurrentBullet -= 1;

	ACPlayer* Player = Cast<ACPlayer>(GetOwner());
	CheckNull(Player);

	Player->GetPlayerWidget()->UpdateCurrentBullet(CurrentBullet);

	// CurrentBullet = FMath::Clamp(CurrentBullet, 0, 30);
}

void ACRifle::Reloading_Implementation()
{
	ASC->TryActivateAbility(ASC->FindAbilitySpecFromClass(UReloadRifle::StaticClass())->Handle);
}

