#include "CAxe.h"
#include "Global.h"
#include "AbilitySystemComponent.h"
#include "GAS/GA/Axe.h"
#include "DataAsset/CWeaponDataAsset.h"

ACAxe::ACAxe()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &RootComp, "RootComp");
	CheckNull(RootComp);

	CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp",RootComp);
	CheckNull(MeshComp);

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

