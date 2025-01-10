#include "CRPG.h"
#include "Global.h"
#include "AbilitySystemComponent.h"
#include "DataAsset/CWeaponDataAsset.h"
#include "GAS/Attribute/CWeaponAttributeSet.h"
#include "GAS/GA/RPG.h"
#include "GAS/GA/Aim.h"

ACRPG::ACRPG()
{
	UStaticMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Assets/Weapon/RPG7_RPG7");
	CheckNull(MeshAsset);

	MeshComp->SetStaticMesh(MeshAsset);
	MeshComp->SetRelativeScale3D(FVector(3));

	AttachSocketName = "hand_r_RPG";
}

void ACRPG::BeginPlay()
{
	Super::BeginPlay();

	CheckNull(ASC);
	CheckNull(Attribute);

	if (ASC)
	{
		FGameplayAbilitySpec AbilitySpec(URPG::StaticClass());
		WeaponAbilitySpec = AbilitySpec;
		ASC->GiveAbility(AbilitySpec);

		FGameplayAbilitySpec SubAbilitySpec(UAim::StaticClass());
		WeaponSubAbilitySpec = SubAbilitySpec;
		ASC->GiveAbility(SubAbilitySpec);
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
}
