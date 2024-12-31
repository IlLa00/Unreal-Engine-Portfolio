#include "CStorm.h"
#include "Global.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "AbilitySystemComponent.h"
#include "Player/CPlayer.h"
#include "Enemy/CEnemy.h"
#include "GAS/Attribute/CMonsterAttributeSet.h"
#include "Pet/CPet.h"
#include "GAS/Attribute/CPetAttributeSet.h"

ACStorm::ACStorm()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &RootComp, "RootComp");
	CheckNull(RootComp);

	CHelpers::CreateSceneComponent(this, &BoxComp, "BoxComp",RootComp);
	CheckNull(BoxComp);

	CHelpers::CreateSceneComponent(this, &ParticleComp, "ParticleComp", RootComp);
	CheckNull(ParticleComp);
	ParticleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CHelpers::CreateActorComponent(this, &ProjectileComp, "ProjectileComp");
	CheckNull(ProjectileComp);
}

void ACStorm::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACStorm::OnBoxBeginOverlap);
}

void ACStorm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACStorm::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner()) return;

	CLog::Print(OtherActor->GetName());

	ACharacter* Character = Cast<ACharacter>(OtherActor);
	CheckNull(Character);

	Character->LaunchCharacter(FVector(0, 0, 1000), false, false);

	// 데미지 처리도 하자.
}

