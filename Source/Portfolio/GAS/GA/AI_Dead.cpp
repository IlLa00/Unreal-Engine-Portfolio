#include "AI_Dead.h"
#include "Global.h"
#include "Pet/CPet.h"
#include "DataAsset/CPetDataAsset.h"
#include "Enemy/CMonster.h"
#include "Enemy/CBoss.h"
#include "DataAsset/CMonsterMeshDataAsset.h"
#include "Item/CItem_HealBuff.h"
#include "Components/ShapeComponent.h"
#include "DataAsset/CMonsterMeshDataAsset.h"
#include "DataAsset/CBossDataAsset.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/CharacterMovementComponent.h"

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
				PrintLine();
				MontageToPlay = Monster->GetDataAsset()->Datas[Monster->GetIndex()].MontageDatas.DeadMontage;
				//Dead(Monster); 
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
				PrintLine();
				MontageToPlay = Boss->GetBossDataAsset()->MontageDatas.DeadMontage;
				Dead(Boss);
			}
		}
	}

	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

	// 어빌리티 종료를 언제해야할까? 일단 죽는 몽타주는 제대로 나오는것 같음.
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

		FTransform FT;
		FT.SetLocation(Monster->GetActorLocation());
		FT.SetRotation(FQuat());

		GetWorld()->SpawnActor<ACItem>(Monster->GetDataAsset()->Datas[Monster->GetIndex()].DropItem, FT);
		
		// EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfoRef(), true, true);
	}
	else if (Character->IsA<ACBoss>())
	{
		ACBoss* Boss = Cast<ACBoss>(Character);
		CheckNull(Boss);

		Boss->GetController()->UnPossess(); // 이걸로 감지컴포넌트 안꺼지면 캐스트하자. 컨트롤러 삭제도해야하지않나?
		
		Boss->GetComponentByClass<UFloatingPawnMovement>()->SetActive(false);

		Boss->GetMesh()->SetSimulatePhysics(true);

		FTransform FT;
		FT.SetLocation(Boss->GetActorLocation());
		FT.SetRotation(FQuat());

		GetWorld()->SpawnActor<ACItem>(Boss->GetBossDataAsset()->DropItem, FT);

		// EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfoRef(), true, true);
	}
	else if (Character->IsA<ACPet>())
	{
		ACPet* Pet = Cast<ACPet>(Character);
		CheckNull(Pet);

		Pet->GetController()->UnPossess();

		// EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfoRef(), true, true);
	}
	
	// 숙련도 증가 <- 숙련도 증가하는걸 위젯에 보이게 하기
	// 피직스는 그대로 두고 데스트로이 함수는 안하는걸로?
}
