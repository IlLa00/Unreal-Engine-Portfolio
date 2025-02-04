#include "AI_Dead.h"
#include "Global.h"
#include "Pet/CPet.h"
#include "DataAsset/CPetDataAsset.h"
#include "Enemy/CMonster.h"
#include "Enemy/CBoss.h"
#include "DataAsset/CMonsterMeshDataAsset.h"
#include "Item/CItem_HealBuff.h"
#include "Components/ShapeComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"
#include "DataAsset/CMonsterMeshDataAsset.h"
#include "DataAsset/CBossDataAsset.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "CAnimInstance.h"


void UAI_Dead::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (OwnerInfo->AvatarActor->IsA<ACPet>())
	{
		ACPet* Pet = Cast<ACPet>(OwnerInfo->AvatarActor);
		if (Pet)
		{
			if (Pet->GetDataAsset())
			{
				MontageToPlay = Pet->GetDataAsset()->MontageDatas.DeadMontage;

				Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);
				Dead(Pet);
			}
		}
	}
	else if (OwnerInfo->AvatarActor->IsA<ACMonster>())
	{
		ACMonster* Monster = Cast<ACMonster>(OwnerInfo->AvatarActor);
		if (Monster)
		{
			if (Monster->GetDataAsset())
			{
				MontageToPlay = Monster->GetDataAsset()->Datas[Monster->GetIndex()].MontageDatas.DeadMontage;

				Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);
				Dead(Monster); 
			}
		}
	}
	else if (OwnerInfo->AvatarActor->IsA<ACBoss>())
	{
		ACBoss* Boss = Cast<ACBoss>(OwnerInfo->AvatarActor);
		if (Boss)
		{

			if (Boss->GetBossDataAsset())
			{
				MontageToPlay = Boss->GetBossDataAsset()->MontageDatas.DeadMontage;

				PrintLine();

				Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);
				Dead(Boss);
			}
		}
	}
}

void UAI_Dead::Dead(ACharacter* Character)
{
	if (Character->IsA<ACMonster>())
	{
		ACMonster* Monster = Cast<ACMonster>(Character);
		CheckNull(Monster);

		Monster->GetController()->UnPossess(); 

		TArray<UShapeComponent*> OutComps;
		Monster->GetComponents<UShapeComponent>(OutComps);

		for (const auto& Comp : OutComps)
		{
			Comp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}

		for (auto& Comp : Monster->GetComponentsByClass(UWidgetComponent::StaticClass()))
		{
			Comp->Deactivate();
		}

		Monster->GetComponentByClass<UTextRenderComponent>()->Deactivate();

		FTransform FT;
		FT.SetLocation(Monster->GetActorLocation());
		FT.SetRotation(FQuat());

		for (const auto& Item : Monster->GetDataAsset()->Datas[Monster->GetIndex()].DropItems)
		{
			GetWorld()->SpawnActor<ACItem>(Item, FT);
		}

		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfoRef(), true, true);
	}
	else if (Character->IsA<ACBoss>())
	{
		ACBoss* Boss = Cast<ACBoss>(Character);
		CheckNull(Boss);

		Boss->GetController()->UnPossess();

		TArray<UShapeComponent*> OutComps;
		Boss->GetComponents<UShapeComponent>(OutComps);

		for (const auto& Comp : OutComps)
		{
			Comp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}

		Boss->GetComponentByClass<UWidgetComponent>()->Deactivate();
		Boss->GetComponentByClass<UTextRenderComponent>()->Deactivate();

		Boss->GetFloatingComp()->Deactivate();
		Boss->GetCharacterMovement()->Activate();

		UCAnimInstance* Anim = Cast<UCAnimInstance>(Boss->GetMesh()->GetAnimInstance());
		CheckNull(Anim);

		Anim->IsFly = false;

		Boss->SetWidget(false);

		FTransform FT;
		FT.SetLocation(Boss->GetActorLocation());
		FT.SetRotation(FQuat());

		GetWorld()->SpawnActor<ACItem>(Boss->GetBossDataAsset()->DropItem, FT);

		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfoRef(), true, true);
	}
	else if (Character->IsA<ACPet>())
	{
		ACPet* Pet = Cast<ACPet>(Character);
		CheckNull(Pet);

		Pet->GetController()->UnPossess();

		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfoRef(), true, true);
	}
}
