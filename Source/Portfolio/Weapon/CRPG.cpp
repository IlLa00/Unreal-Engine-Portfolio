#include "CRPG.h"
#include "Global.h"
#include "AbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "DataAsset/CWeaponDataAsset.h"
#include "GAS/Attribute/CWeaponAttributeSet.h"
#include "GAS/GA/RPG.h"
#include "GAS/GA/Aim.h"
#include "Weapon/CRocket.h"
#include "Interface/CAIInterface.h"
#include "GAS/Attribute/CAIAttributeSet.h"
#include "Player/CPlayer.h"
#include "GAS/Attribute/CCharacterAttributeSet.h"
#include "Particles/ParticleSystem.h"

ACRPG::ACRPG()
{
	UStaticMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Assets/Weapon/RPG7_RPG7");
	CheckNull(MeshAsset);

	MeshComp->SetStaticMesh(MeshAsset);
	MeshComp->SetRelativeScale3D(FVector(3));

	CHelpers::CreateSceneComponent(this, &SplineComp, "SplineComp", RootComp);
	CheckNull(SplineComp);

	CHelpers::GetAsset(&ExplosionParticle, "/Game/Assets/Explosions/Particles/P_ImpactExplosion4");
	CheckNull(ExplosionParticle);

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

void ACRPG::SphereTrace(FVector Location)
{
	TArray<AActor*> Ignores;
	TArray<FHitResult> HitResults;

	if(UKismetSystemLibrary::SphereTraceMultiByProfile(GetWorld(), Location, Location, 250.f, "Pawn", true, Ignores, EDrawDebugTrace::Persistent, HitResults,false))
	{
		for (auto& HitResult : HitResults)
		{
			if (HitResult.GetActor()->GetClass()->ImplementsInterface(UCAIInterface::StaticClass()))
			{
				ICAIInterface* AI = Cast<ICAIInterface>(HitResult.GetActor());
				CheckNull(AI);

				AI->GetAIAttributeSet()->Attack(AI->GetAIAttributeSet()->GetCurrentHealth() - Attribute->GetCurrentDamage(), this);
			}
			else if(HitResult.GetActor()->IsA<ACPlayer>())
			{
				ACPlayer* Player = Cast<ACPlayer>(HitResult.GetActor());
				CheckNull(Player);

				Player->GetAttributeSet()->SetCurrentHealth(Player->GetAttributeSet()->GetCurrentHealth() - Attribute->GetCurrentDamage());
			}
		}
	}

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, Location);
}
