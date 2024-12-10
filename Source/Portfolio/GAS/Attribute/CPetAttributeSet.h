#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CPetAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class PORTFOLIO_API UCPetAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UCPetAttributeSet();

    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData BaseHealth;
	ATTRIBUTE_ACCESSORS(UCPetAttributeSet, BaseHealth);

	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UCPetAttributeSet, CurrentHealth);

	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData BaseAttack;
	ATTRIBUTE_ACCESSORS(UCPetAttributeSet, BaseAttack);

	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CurrentAttack;
	ATTRIBUTE_ACCESSORS(UCPetAttributeSet, CurrentAttack);
};
