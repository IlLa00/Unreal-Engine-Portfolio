#include "CMonsterAttributeSet.h"
#include "Global.h"

UCMonsterAttributeSet::UCMonsterAttributeSet()
{

}

void UCMonsterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
}

void UCMonsterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	// 프로젝타일과 부딪히면 여기까지 잘 들어옴
}

void UCMonsterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
}
