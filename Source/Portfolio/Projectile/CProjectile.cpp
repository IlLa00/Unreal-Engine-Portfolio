#include "CProjectile.h"
#include "Global.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "Player/CPlayer.h"
#include "Enemy/CEnemy.h"
#include "GAS/GE/Damage.h"

ACProjectile::ACProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &RootComp, "RootComp");
	CheckNull(RootComp);

	CHelpers::CreateSceneComponent(this, &ParticleComp, "ParticleComp", RootComp);
	CheckNull(ParticleComp);

	CHelpers::CreateSceneComponent(this, &BoxComp, "BoxComp", RootComp);
	CheckNull(BoxComp);

	CHelpers::CreateActorComponent(this, &ProjectileComp, "ProjectileComp");
	CheckNull(ProjectileComp);
}

void ACProjectile::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACProjectile::OnBoxBeginOverlap);

}

void ACProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACProjectile::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 여기서 부딪힌 곳에 피격 파티클 추가 + 액터 삭제 + (사운드 추가)

	if (OtherActor->IsA<ACPlayer>())
		return;

	if (OtherActor->IsA<ACEnemy>())
	{
		PrintLine();
		ACEnemy* Enemy = Cast<ACEnemy>(OtherActor);
		if (Enemy && Enemy->GetAbilitySystemComponent())
		{
			UDamage* GE = NewObject<UDamage>(this, UDamage::StaticClass());

			FGameplayEffectContextHandle EffectContext = Enemy->GetAbilitySystemComponent()->MakeEffectContext();
			FGameplayEffectSpecHandle EffectSpecHandle = Enemy->GetAbilitySystemComponent()->MakeOutgoingSpec(GE->GetClass(), 1.0f, EffectContext);
			FGameplayEffectSpec* EffectSpec = EffectSpecHandle.Data.Get();

			GE->SetModify(GetOwner(), Enemy);

			Enemy->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpec, Enemy->GetAbilitySystemComponent());	
		}
	}
}

