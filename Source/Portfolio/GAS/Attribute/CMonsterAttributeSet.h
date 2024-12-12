#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CMonsterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class PORTFOLIO_API UCMonsterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UCMonsterAttributeSet();
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData BaseHealth;
	ATTRIBUTE_ACCESSORS(UCMonsterAttributeSet, BaseHealth);

	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UCMonsterAttributeSet, CurrentHealth);

	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData BaseDamage;
	ATTRIBUTE_ACCESSORS(UCMonsterAttributeSet, BaseDamage);

	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CurrentDamage;
	ATTRIBUTE_ACCESSORS(UCMonsterAttributeSet, CurrentDamage);
};
