#include "GAS/GA/Rifle.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Camera/CameraComponent.h"

URifle::URifle()
{
	CHelpers::GetAsset(&AttackMontage, "/Game/Assets/Montage/Fire_Rifle_Ironsights_Montage");
	CheckNull(AttackMontage);
}

void URifle::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACPlayer* Player = Cast<ACPlayer>(ActorInfo->AvatarActor->GetOwner());
	CheckNull(Player);

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

	CLog::Print(Start);
	CLog::Print(End);

	TArray<AActor*> IgnoreActors;

	FHitResult OutHit;
	UKismetSystemLibrary::LineTraceSingleByProfile(GetWorld(), Start, End, "Pawn", false, IgnoreActors, EDrawDebugTrace::ForOneFrame, OutHit, true);
	
	if (OutHit.GetActor())
		CLog::Print(OutHit.GetActor()->GetName());
}
