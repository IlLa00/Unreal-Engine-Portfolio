#include "HookGun.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Camera/CameraComponent.h"
#include "Engine/TimerHandle.h"
#include "Weapon/CHookGun.h"
#include "CableComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UHookGun::UHookGun()
{
	CHelpers::GetAsset(&AttackMontage, "/Game/Assets/Montage/Fire_Rifle_Ironsights_Montage");
	CheckNull(AttackMontage);
}

void UHookGun::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACPlayer* Player = Cast<ACPlayer>(GetOwningActorFromActorInfo()->GetOwner());
	CheckNull(Player);

	Player->PlayAnimMontage(AttackMontage); // 발사 몽타주

	if (!GetWorld()->GetTimerManager().IsTimerActive(TraceTimerHandle)) // 0.1초마다 실행.
	{
		GetWorld()->GetTimerManager().SetTimer(TraceTimerHandle, this, &UHookGun::FireHook, 0.05f, true);
	}

	if (!GetWorld()->GetTimerManager().IsTimerActive(EndTimerHandle)) // 1초뒤에 어빌리티 종료.
	{
		GetWorld()->GetTimerManager().SetTimer(EndTimerHandle, this, &UHookGun::FireEnd, 1.f, false);
	}
}

void UHookGun::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	if (GetWorld()->GetTimerManager().IsTimerActive(TraceTimerHandle)) return; // 마우스로 종료되는거 막기 위함. 이 어빌리티는 어빌리티 자체에서 실패판단할 것임.
	
	ACHookGun* HookGun = Cast<ACHookGun>(GetOwningActorFromActorInfo());
	CheckNull(HookGun);

	ACPlayer* Player = Cast<ACPlayer>(HookGun->GetOwner());
	CheckNull(Player);

	GetWorld()->GetTimerManager().ClearTimer(EndTimerHandle);

	HookGun->GetCableComp()->CableLength = 0.f; // 케이블 기본길이

	//HookGun->GetCableComp()->bAttachEnd = false;
	HookGun->GetCableComp()->EndLocation = FVector(0);

	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UHookGun::FireHook()
{
	if (!this->IsActive()) return; // 어빌리티 실행중일때만 진입

	ACHookGun* HookGun = Cast<ACHookGun>(GetOwningActorFromActorInfo());
	CheckNull(HookGun);

    ACPlayer* Player = Cast<ACPlayer>(HookGun->GetOwner());
    CheckNull(Player);

    FVector Start = HookGun->GetActorLocation();
    FVector End = Start + Player->GetCameraComp()->GetForwardVector() * HookGun->GetCableComp()->CableLength;

    FHitResult HitResult;
    TArray<AActor*> IgnoreActors;

	FCollisionObjectQueryParams Parms;
	Parms.AddObjectTypesToQuery(ECC_WorldStatic);

	if (GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, Parms))
	{
		HookGun->GetCableComp()->EndLocation = HitResult.Location;

		SplineLaunch(HitResult.Location);

		GetWorld()->GetTimerManager().ClearTimer(TraceTimerHandle);

		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
	}
    else
	{
		HookGun->GetCableComp()->EndLocation = HookGun->GetTransform().InverseTransformPosition(End); // 로컬 스페이스로 변환
        HookGun->GetCableComp()->CableLength += 200.f;
    }
}

void UHookGun::SplineLaunch(FVector HitLocation)
{
	ACHookGun* HookGun = Cast<ACHookGun>(GetOwningActorFromActorInfo());
	CheckNull(HookGun);

	ACPlayer* Player = Cast<ACPlayer>(HookGun->GetOwner());
	CheckNull(Player);

	HookGun->GetSplineComp()->AddSplinePoint(Player->GetActorLocation(), ESplineCoordinateSpace::World);
	HookGun->GetSplineComp()->AddSplinePoint(HitLocation, ESplineCoordinateSpace::World);
	HookGun->GetSplineComp()->UpdateSpline();

	FVector LaunchLocation = HookGun->GetSplineComp()->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
	FVector LaunchDirection = (LaunchLocation - Player->GetActorLocation()).GetSafeNormal();

	Player->LaunchCharacter(LaunchDirection * 3000.f, true, true);
}

void UHookGun::FireEnd()
{
	GetWorld()->GetTimerManager().ClearTimer(TraceTimerHandle);
	
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
}

