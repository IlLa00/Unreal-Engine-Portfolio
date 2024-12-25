#include "CSword.h"
#include "Global.h"
#include "AbilitySystemComponent.h"
#include "GAS/Attribute/CWeaponAttributeSet.h"
#include "GameplayTagContainer.h"
#include "GAS/GA/Sword.h"
#include "DataAsset/CWeaponDataAsset.h"

ACSword::ACSword()
{
	UStaticMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Assets/KlianLowPoliSwords/Mesh/SM_LargeSword");
	CheckNull(MeshAsset);

	MeshComp->SetStaticMesh(MeshAsset);

	AttachSocketName = "hand_r_Sword";

}

void ACSword::BeginPlay()
{
	Super::BeginPlay();

	if (ASC)
	{
		FGameplayAbilitySpec AbilitySpec(USword::StaticClass());
		WeaponAbilitySpec = AbilitySpec;
		ASC->GiveAbility(AbilitySpec);
	}

	for (const auto& data : DataAsset->Datas)
	{
		if (GetClass() == data.WeaponClass)
		{
			Attribute->SetBaseDamage(data.BaseDamage);
			Attribute->SetBaseProficiency(data.BaseProficiency);

			Attribute->SetCurrentDamage(Attribute->GetBaseDamage());
			Attribute->SetCurrentProficiency(Attribute->GetBaseProficiency());

			if(data.WeaponImage)
				WeaponImage = data.WeaponImage;

			if (data.WeaponName != NAME_None)
				WeaponName = FText::FromString(data.WeaponName.ToString());
			break;
		}
	}
}

void ACSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
