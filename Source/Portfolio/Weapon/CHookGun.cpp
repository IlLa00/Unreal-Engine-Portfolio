#include "CHookGun.h"
#include "Global.h"
#include "AbilitySystemComponent.h"
#include "GAS/GA/HookGun.h"
#include "GAS/GA/Aim.h"

ACHookGun::ACHookGun()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &RootComp, "RootComp");
	CheckNull(RootComp);

	CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp", RootComp);
	CheckNull(MeshComp);

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


}

void ACHookGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
