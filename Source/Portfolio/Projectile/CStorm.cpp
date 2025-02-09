#include "CStorm.h"
#include "Global.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "AbilitySystemComponent.h"
#include "Player/CPlayer.h"
#include "Enemy/CEnemy.h"
#include "Enemy/CBoss.h"
#include "Pet/CPet.h"
#include "GAS/Attribute/CCharacterAttributeSet.h"
#include "GAS/Attribute/CAIAttributeSet.h"

ACStorm::ACStorm()
{
	CHelpers::CreateSceneComponent(this, &RootGravityComp, "RootGravityComp");
	CheckNull(RootGravityComp);

	CHelpers::CreateSceneComponent(this, &BoxComp, "BoxComp", RootGravityComp);
	CheckNull(BoxComp);

	CHelpers::CreateSceneComponent(this, &ParticleComp, "ParticleComp", RootGravityComp);
	CheckNull(ParticleComp);
	ParticleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CHelpers::CreateActorComponent(this, &ProjectileComp, "ProjectileComp");
	CheckNull(ProjectileComp);

	SetLifeSpan(8.f);
}

void ACStorm::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACStorm::OnBoxBeginOverlap);
}

void ACStorm::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner()) return;

	ACBoss* Boss = Cast<ACBoss>(GetOwner());
	CheckNull(Boss);

	if (OtherActor->IsA<ACPlayer>())
	{
		ACPlayer* Player = Cast<ACPlayer>(OtherActor);
		CheckNull(Player);

		Player->LaunchCharacter(FVector(0, 0, 100), false, false);

		if(Player->GetAttributeSet())
			Player->GetAttributeSet()->SetCurrentHealth(Player->GetAttributeSet()->GetCurrentHealth() - Boss->GetAIAttributeSet()->GetCurrentDamage());
	}
	else if (OtherActor->IsA<ACPet>())
	{
		ACPet* Pet = Cast<ACPet>(OtherActor);
		CheckNull(Pet);

		Pet->LaunchCharacter(FVector(0, 0, 100), false, false);

		if (Pet->GetAIAttributeSet())
			Pet->GetAIAttributeSet()->SetCurrentHealth(Pet->GetAIAttributeSet()->GetCurrentHealth() - Boss->GetAIAttributeSet()->GetCurrentDamage());
	}
	
}

