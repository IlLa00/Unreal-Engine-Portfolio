#include "AI_Dead.h"
#include "Global.h"
#include "Pet/CPet.h"
#include "DataAsset/CPetDataAsset.h"
#include "Enemy/CEnemy.h"
#include "DataAsset/CMonsterMeshDataAsset.h"
#include "Item/CItem_HealBuff.h"
#include "Components/ShapeComponent.h"
#include "DataAsset/CMonsterMeshDataAsset.h"

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
			}
		}
	}
	else if (OwnerInfo->AvatarActor->IsA<ACEnemy>())
	{
		ACEnemy* Enemy = Cast<ACEnemy>(OwnerInfo->AvatarActor);
		if (Enemy)
		{
			if (Enemy->GetDataAsset())
			{
				PrintLine();
				MontageToPlay = Enemy->GetDataAsset()->Datas[Enemy->GetIndex()].MontageDatas.DeadMontage;
				Dead(Enemy); // 아무리봐도 인터페이스가 있어야할지도?
			}
		}
	}

	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);
}

void UAI_Dead::Dead(ACharacter* Character)
{
	// 이렇게 분류하는게 맞을까싶음 인터페이스 쓸생각하자
	if (Character->IsA<ACEnemy>())
	{
		ACEnemy* Enemy = Cast<ACEnemy>(Character);
		CheckNull(Enemy);

		Enemy->GetController()->UnPossess(); // 이걸로 감지컴포넌트 안꺼지면 캐스트하자. 컨트롤러 삭제도해야하지않나?

		TArray<UShapeComponent*> OutComps;
		Enemy->GetComponents<UShapeComponent>(OutComps);

		for (const auto& Comp : OutComps)
		{
			Comp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}

		FTransform FT;
		FT.SetLocation(Enemy->GetActorLocation());
		FT.SetRotation(FQuat());

		GetWorld()->SpawnActor<ACItem>(Enemy->GetDataAsset()->Datas[Enemy->GetIndex()].DropItem, FT);
		// GetWorld()->SpawnActor<ACItem>(Enemy->GetActorLocation(), FRotator()); // 스폰되자마 비긴오버랩 호출되어버림 그래서 이거 앞으로 콜리전꺼야됨

	}
	
	// 숙련도 증가 <- 숙련도 증가하는걸 위젯에 보이게 하기
	// 피직스는 그대로 두고 데스트로이 함수는 안하는걸로?
}
