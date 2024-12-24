#include "CMonsterAttributeSet.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "Widget/CEnemyHealthWidget.h"

UCMonsterAttributeSet::UCMonsterAttributeSet()
{

}

void UCMonsterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
}

void UCMonsterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	if (OldValue > NewValue) // 체력이 감소했으면
	{
		ACEnemy* Enemy = Cast<ACEnemy>(GetOwningActor());
		if (Enemy)
		{
			Enemy->GetHealthWidget()->Update(NewValue, GetBaseHealth()); // 델리게이트로 해보자.

			Enemy->GetTagContainer().Reset();
			Enemy->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag(FName("AI.State.GetHit")));
		}
		// 맞는 몽타주 <- 이건 데이터에셋 안에 몽타주를 재생한다는 뜻인데 어틜뷰트에서 하는게 맞나?
		// 머리위에 느낌표
	}
}

void UCMonsterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
}
