#include "CHookGun.h"
#include "Global.h"
#include "AbilitySystemComponent.h"
#include "GAS/GA/HookGun.h"
#include "GAS/GA/Aim.h"
#include "DataAsset/CWeaponDataAsset.h"
#include "CableComponent.h"
#include "Components/SplineComponent.h"

ACHookGun::ACHookGun()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &RootComp, "RootComp");
	CheckNull(RootComp);

	CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp", RootComp);
	CheckNull(MeshComp);

	CHelpers::CreateSceneComponent(this, &CableComp, "CableComp", RootComp);
	CheckNull(CableComp);

	CHelpers::CreateSceneComponent(this, &SplineComp, "SplineComp", RootComp);
	CheckNull(SplineComp);

	UStaticMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Assets/Weapon/lowpolyGun");
	CheckNull(MeshAsset);

	MeshComp->SetStaticMesh(MeshAsset);

	AttachSocketName = "hand_r_HookGun";
}

void ACHookGun::BeginPlay()
{
	Super::BeginPlay();

	if (ASC)
	{
		FGameplayAbilitySpec AbilitySpec(UHookGun::StaticClass());
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
			if (data.WeaponImage)
				WeaponImage = data.WeaponImage;

			if (data.WeaponName != NAME_None)
				WeaponName = FText::FromString(data.WeaponName.ToString());
			break;
		}
	}

}

void ACHookGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
