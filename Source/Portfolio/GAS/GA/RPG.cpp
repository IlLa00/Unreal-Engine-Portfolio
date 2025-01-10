#include "GAS/GA/RPG.h"
#include "Global.h"
#include "Weapon/CRPG.h"
#include "Player/CPlayer.h"
#include "Camera/CameraComponent.h"
#include "Engine/StaticMeshSocket.h"

URPG::URPG()
{
	CHelpers::GetClass(&Rocket, "/Game/Weapon/BP_Rocket");
	CheckNull(Rocket);
}

void URPG::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACRPG* RPG = Cast<ACRPG>(ActorInfo->AvatarActor);
	CheckNull(RPG);

	ACPlayer* Player = Cast<ACPlayer>(ActorInfo->AvatarActor->GetOwner());
	CheckNull(Player);

	UStaticMeshComponent* MeshComp = RPG->GetComponentByClass<UStaticMeshComponent>();
	CheckNull(MeshComp);

	GetWorld()->SpawnActor<AActor>(Rocket, MeshComp->GetSocketLocation("FireLocation"), Player->GetCameraComp()->GetForwardVector().Rotation());
}

void URPG::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);


}
