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

	FTransform SpawnTM; 
	SpawnTM.SetLocation(ActorInfo->AvatarActor->GetActorLocation() + FVector(0, 100, 0));

	// FActorSpawnParameters SpawnParams; 그럼 있을 필요가 없쥬?
	// SpawnParams.Owner = Cast<AActor>(ActorInfo->AvatarActor);

	Pet = ActorInfo->OwnerActor->GetWorld()->SpawnActor<ACPet>(PetClass, SpawnTM);
	CheckNull(Pet);

	PetController->Possess(Pet); // 여기서 오너가 바뀜, SetOwner()가 있음
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
