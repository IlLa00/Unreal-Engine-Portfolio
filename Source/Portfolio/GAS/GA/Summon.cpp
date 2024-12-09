#include "Summon.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Pet/CPetController.h"
#include "Pet/CPet.h"

USummon::USummon()
{
	CHelpers::GetClass(&PetClass, "/Game/Pet/BP_CPet");
	CheckNull(PetClass);
}

void USummon::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	PetController = ActorInfo->OwnerActor->GetWorld()->SpawnActor<ACPetController>(ACPetController::StaticClass());
	CheckNull(PetController);

	FTransform SpawnTM; // Todo.. 나중에 위치나 회전 고려해보기
	SpawnTM.SetLocation(ActorInfo->AvatarActor->GetActorLocation() + FVector(0, 100, 0));
	// SpawnTM.SetRotation(FQuat(ActorInfo->PlayerController->PlayerCameraManager->GetCameraRotation()));

	Pet = ActorInfo->OwnerActor->GetWorld()->SpawnActor<ACPet>(PetClass, SpawnTM);
	CheckNull(Pet);

	PetController->Possess(Pet);
}

void USummon::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	if (PetController)
	{
		PetController->UnPossess();
		PetController->Destroy();
	}
		
	if(Pet)
		Pet->Destroy();
}
