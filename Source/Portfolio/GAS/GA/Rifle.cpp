#include "GAS/GA/Rifle.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Camera/CameraComponent.h"
#include "Enemy/CEnemy.h"
#include "GAS/Attribute/CMonsterAttributeSet.h"
#include "Weapon/CRifle.h"
#include "GAS/Attribute/CWeaponAttributeSet.h"

URifle::URifle()
{
	CHelpers::GetAsset(&AttackMontage, "/Game/Assets/Montage/Fire_Rifle_Ironsights_Montage");
	CheckNull(AttackMontage);
}

void URifle::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &URifle::Shoot, 0.1f, true);
}

void URifle::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void URifle::Shoot()
{
	ACPlayer* Player = Cast<ACPlayer>(GetOwningActorFromActorInfo()->GetOwner());
	CheckNull(Player);

	Player->PlayAnimMontage(AttackMontage);

	FVector Start = Player->GetCameraComp()->GetComponentLocation() + Player->GetCameraComp()->GetForwardVector() * 100.f;
	FVector End = Start + Player->GetCameraComp()->GetForwardVector() * 2000.f;

	TArray<AActor*> IgnoreActors;

	FHitResult HitResult;

	FCollisionObjectQueryParams Parms;
	Parms.AddObjectTypesToQuery(ECC_Pawn);

	if (GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, Parms))
	{
		ACEnemy* Enemy = Cast<ACEnemy>(HitResult.GetActor());
		CheckNull(Enemy);

		ACRifle* Rifle = Cast<ACRifle>(GetOwningActorFromActorInfo());
		CheckNull(Rifle);

		Enemy->GetAttributeSet()->SetCurrentHealth(Enemy->GetAttributeSet()->GetCurrentHealth() - Rifle->GetAttiribute()->GetCurrentDamage());
	}
}
