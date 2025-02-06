#include "CWeapon.h"
#include "Global.h"
#include "DataAsset/CWeaponDataAsset.h"
#include "GAS/Attribute/CWeaponAttributeSet.h"
#include "Components/BoxComponent.h"
#include "Enemy/CEnemy.h"
#include "Interface/CAIInterface.h"
#include "GAS/Attribute/CAIAttributeSet.h"

ACWeapon::ACWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &RootComp, "RootComp");
	CheckNull(RootComp);

	CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp", RootComp);
	CheckNull(MeshComp);

	CHelpers::CreateSceneComponent(this, &AttackCollisionComp, "AttackCollisionComp", MeshComp);
	CheckNull(AttackCollisionComp);

	Attribute = CreateDefaultSubobject<UCWeaponAttributeSet>("Attribute");
	CheckNull(Attribute);

	CHelpers::GetAsset(&DataAsset, "/Game/DataAsset/DA_Weapon");
	CheckNull(DataAsset);

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>("ASC");
	CheckNull(ASC);

	CHelpers::GetClass(&BPDamageBuffEffect, "/Game/GAS/BP_GE_DamageBuff");
	CheckNull(BPDamageBuffEffect);

	CHelpers::GetClass(&BPProficencyEffect, "/Game/GAS/BP_GE_UpdateWeaponProficiency");
	CheckNull(BPProficencyEffect);
	
}

void ACWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	if(ASC)
		ASC->InitAbilityActorInfo(this, this);

	if (AttackCollisionComp)
	{
		AttackCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ACWeapon::BeginOverlap);
	}

	if (Attribute)
		Attribute->OnUpdateProficiency.AddDynamic(this, &ACWeapon::UpdateProficiency);

}

void ACWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UAbilitySystemComponent* ACWeapon::GetAbilitySystemComponent() const
{
	return ASC;
}

void ACWeapon::OnDamageBuff()
{
	FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();

	DamageBuffEffectHandle = ASC->MakeOutgoingSpec(BPDamageBuffEffect, 1.0f, EffectContext);

	ASC->ApplyGameplayEffectSpecToSelf(*DamageBuffEffectHandle.Data.Get());
}

void ACWeapon::UpdateProficiency(float NewValue)
{
	FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();

	ProficiencyEffectHandle = ASC->MakeOutgoingSpec(BPProficencyEffect, 1.0f, EffectContext);

	ASC->ApplyGameplayEffectSpecToSelf(*ProficiencyEffectHandle.Data.Get());
}

void ACWeapon::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner()) return;

	if (OtherActor->IsA<ACEnemy>())
	{
		ICAIInterface* AI = Cast<ICAIInterface>(OtherActor);
		CheckNull(AI);

		AI->GetAIAttributeSet()->Attack(AI->GetAIAttributeSet()->GetCurrentHealth() - GetAttiribute()->GetCurrentDamage(), this);
	}
}


