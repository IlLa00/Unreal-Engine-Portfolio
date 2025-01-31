#include "CItem.h"
#include "Global.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "DataAsset/CItemDataAsset.h"

ACItem::ACItem()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &RootGravityComp, "RootGravityComp");
	CheckNull(RootGravityComp);

	CHelpers::CreateSceneComponent(this, &BoxComp, "BoxComp", RootGravityComp);
	CheckNull(BoxComp);

	CHelpers::GetAsset(&DataAsset, "/Game/DataAsset/DA_Item");
	CheckNull(DataAsset);

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>("ASC");
	CheckNull(ASC);
}

void ACItem::BeginPlay()
{
	Super::BeginPlay();
	
	if (ASC)
		ASC->InitAbilityActorInfo(this, this);

	if(BoxComp)
		BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACItem::BeginOverlap);
}

void ACItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UAbilitySystemComponent* ACItem::GetAbilitySystemComponent() const
{
	return ASC;
}

void ACItem::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}


