#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CWeaponAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

class UCWeaponDataAsset;

UCLASS()
class PORTFOLIO_API UCWeaponAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

private:
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute", meta = (AllowPrivateAccess = true))
		FGameplayAttributeData BaseDamage;
	ATTRIBUTE_ACCESSORS(UCWeaponAttributeSet, BaseDamage);

	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute", meta = (AllowPrivateAccess = true))
		FGameplayAttributeData CurrentDamage;
	ATTRIBUTE_ACCESSORS(UCWeaponAttributeSet, CurrentDamage);

	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute", meta = (AllowPrivateAccess = true))
		FGameplayAttributeData BaseProficiency;
	ATTRIBUTE_ACCESSORS(UCWeaponAttributeSet, BaseProficiency);

	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute", meta = (AllowPrivateAccess = true))
		FGameplayAttributeData CurrentProficiency;
	ATTRIBUTE_ACCESSORS(UCWeaponAttributeSet, CurrentProficiency);
};
