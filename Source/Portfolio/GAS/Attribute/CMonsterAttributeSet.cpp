#include "CMonsterAttributeSet.h"
#include "Global.h"
#include "Enemy/CMonster.h"
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
	//ACMonster* Monster = Cast<ACMonster>(GetOwningActor());
	//CheckNull(Monster);

	//if (NewValue <= 0.f) // 죽었으면
	//{
	//	TagHelpers::AIChangeStateTag(Monster->GetTagContainer(), "AI.Action.Dead");
	//}

	//if (OldValue > NewValue) // 체력이 감소했으면
	//{
	//	TagHelpers::AIChangeStateTag(Monster->GetTagContainer(), "AI.Action.GetHit");

	//	Monster->GetHealthWidget()->Update(NewValue, GetBaseHealth()); // 델리게이트로 해보자.
	//}
}

void UCMonsterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
}
