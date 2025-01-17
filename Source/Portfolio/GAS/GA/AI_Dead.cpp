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

				PrintLine();

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

				Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);
				Dead(Boss);
			}
		}
	}
}

void UAI_Dead::Dead(ACharacter* Character)
{
	// 이렇게 분류하는게 맞을까싶음 인터페이스 쓸생각하자
	if (Character->IsA<ACMonster>())
	{
		ACMonster* Monster = Cast<ACMonster>(Character);
		CheckNull(Monster);

		Monster->GetController()->UnPossess(); // 이걸로 감지컴포넌트 안꺼지면 캐스트하자. 컨트롤러 삭제도해야하지않나?

		TArray<UShapeComponent*> OutComps;
		Monster->GetComponents<UShapeComponent>(OutComps);

		for (const auto& Comp : OutComps)
		{
			Comp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}

		Monster->GetComponentByClass<UWidgetComponent>()->Deactivate();

		FTransform FT;
		FT.SetLocation(Monster->GetActorLocation());
		FT.SetRotation(FQuat());

		GetWorld()->SpawnActor<ACItem>(Monster->GetDataAsset()->Datas[Monster->GetIndex()].DropItem, FT);

		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfoRef(), true, true);
	}
	else if (Character->IsA<ACBoss>())
	{
		ACBoss* Boss = Cast<ACBoss>(Character);
		CheckNull(Boss);

		Boss->GetController()->UnPossess(); 

		Boss->GetMesh()->SetSimulatePhysics(true);
		Boss->GetComponentByClass<UTextRenderComponent>()->SetActive(false);

		/*TArray<UActorComponent*> Comps;
		Boss->GetComponents(Comps);*/

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
