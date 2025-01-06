#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CAIAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAIHealthChanged, float, NewHealth, float, BaseHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAIDamageChanged, float, NewDamage, float, BaseDamage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDamaged, float, NewValue);

UCLASS()
class PORTFOLIO_API UCAIAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData BaseHealth;
	ATTRIBUTE_ACCESSORS(UCAIAttributeSet, BaseHealth);

	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UCAIAttributeSet, CurrentHealth);

	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData BaseDamage;
	ATTRIBUTE_ACCESSORS(UCAIAttributeSet, BaseDamage);

	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CurrentDamage;
	ATTRIBUTE_ACCESSORS(UCAIAttributeSet, CurrentDamage);

public:
	void Attack(float Value, AActor* DamageCauser);

public:
	FAIHealthChanged OnHealthChange;
	FAIDamageChanged OnDamageChange;

	FDamaged OnDamaged;

	AActor* LastDamageCauser;
};
