#include "CWeapon.h"
#include "Global.h"
#include "DataAsset/CWeaponDataAsset.h"
#include "GAS/Attribute/CWeaponAttributeSet.h"
#include "Components/CapsuleComponent.h"

ACWeapon::ACWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	Attribute = CreateDefaultSubobject<UCWeaponAttributeSet>("Attribute");
	CheckNull(Attribute);

	CHelpers::GetAsset(&DataAsset, "/Game/DataAsset/DA_Weapon");
	CheckNull(DataAsset);

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>("ASC");
	CheckNull(ASC);

	CHelpers::CreateSceneComponent(this, &AttackComp, "AttackComp");
	CheckNull(AttackComp);
}

void ACWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	if(ASC)
		ASC->InitAbilityActorInfo(this, this);

	if (AttackComp->IsActive())
		AttackComp->OnComponentBeginOverlap.AddDynamic(this, &ACWeapon::BeginOverlap);
}

void ACWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UAbilitySystemComponent* ACWeapon::GetAbilitySystemComponent() const
{
	return ASC;
}

void ACWeapon::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PrintLine();
}


