#include "CAxe.h"
#include "Global.h"
#include "AbilitySystemComponent.h"
#include "GAS/Attribute/CWeaponAttributeSet.h"
#include "GAS/GA/Axe.h"
#include "DataAsset/CWeaponDataAsset.h"
#include "Components/BoxComponent.h"

ACAxe::ACAxe()
{
	PrimaryActorTick.bCanEverTick = true;

	UStaticMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Assets/Axe/fire_axe");
	CheckNull(MeshAsset);

	MeshComp->SetStaticMesh(MeshAsset);

	AttachSocketName = "hand_r_Axe";
}

void ACAxe::BeginPlay()
{
	Super::BeginPlay();

	if (ASC)
	{
		FGameplayAbilitySpec AbilitySpec(UAxe::StaticClass());
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
			Attribute->SetCurrentProficiency(0.f);

			if (data.WeaponImage)
				WeaponImage = data.WeaponImage;

			if (data.WeaponName != NAME_None)
				WeaponName = FText::FromString(data.WeaponName.ToString());
			break;
		}
	}		
}

void ACAxe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


