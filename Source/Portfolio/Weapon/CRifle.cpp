#include "CRifle.h"
#include "Global.h"
#include "AbilitySystemComponent.h"
#include "DataAsset/CWeaponDataAsset.h"
#include "GAS/Attribute/CWeaponAttributeSet.h"
#include "GAS/GA/Rifle.h"

ACRifle::ACRifle()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &RootComp, "RootComp");
	CheckNull(RootComp);
	
	CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp",RootComp);
	CheckNull(MeshComp);

	UStaticMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Assets/Weapon/lowpolyRifle");
	CheckNull(MeshAsset);

	MeshComp->SetStaticMesh(MeshAsset);
	MeshComp->SetRelativeScale3D(FVector(0.2));

	/*Attribute = CreateDefaultSubobject<UCWeaponAttributeSet>("Attribute");
	CheckNull(Attribute);*/
}

void ACRifle::BeginPlay()
{
	Super::BeginPlay();

	CheckNull(ASC);
	CheckNull(Attribute);

	if (ASC)
	{
		FGameplayAbilitySpec AbilitySpec(URifle::StaticClass());
		ASC->GiveAbility(AbilitySpec);
	}


	for (const auto& data : DataAsset->Datas)
	{
		if (GetClass() == data.WeaponClass)
		{
			PrintLine();
			Attribute->SetBaseDamage(data.BaseDamage);
			Attribute->SetBaseProficiency(data.BaseProficiency);
			break;
		}
	}


	if (Attribute)
	{
		CLog::Print(Attribute->GetBaseDamage()); // ¿Ö 0¶ä?
		CLog::Print(Attribute->GetBaseProficiency()); // ¿Ö 0¶ä?
	}
	
}

void ACRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

