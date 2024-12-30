#include "CRifle.h"
#include "Global.h"
#include "AbilitySystemComponent.h"
#include "DataAsset/CWeaponDataAsset.h"
#include "GAS/Attribute/CWeaponAttributeSet.h"
#include "GAS/GA/Rifle.h"
#include "GAS/GA/Aim.h"
#include "GAS/GA/ReloadRifle.h"

ACRifle::ACRifle()
{
	PrimaryActorTick.bCanEverTick = true;

	UStaticMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Assets/Weapon/lowpolyRifle");
	CheckNull(MeshAsset);

	MeshComp->SetStaticMesh(MeshAsset);
	MeshComp->SetRelativeScale3D(FVector(0.2));

	AttachSocketName = "hand_r_Rifle";

	bullet = 30;

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
			Attribute->SetCurrentProficiency(Attribute->GetBaseProficiency());

			if (data.WeaponImage)
				WeaponImage = data.WeaponImage;

			if (data.WeaponName != NAME_None)
				WeaponName = FText::FromString(data.WeaponName.ToString());
			break;
		}
	}
}

void ACRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACRifle::Reload()
{
	bullet = 30;
}

void ACRifle::Shooting_Implementation()
{
	if (IsReload())
		return;

	if (bullet <= 0)
	{
		bReload = true;
		Reloading();
		return;
	}

	bullet -= 1;

	bullet = FMath::Clamp(bullet, 0, 30);
	CLog::Print(bullet);

}

void ACRifle::Reloading_Implementation()
{
	ASC->TryActivateAbility(ASC->FindAbilitySpecFromClass(UReloadRifle::StaticClass())->Handle);
}

