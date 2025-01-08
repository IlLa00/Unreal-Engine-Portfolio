//#pragma once
//
//#include "CoreMinimal.h"
//#include "AttributeSet.h"
//#include "AbilitySystemComponent.h"
//#include "CPetAttributeSet.generated.h"
//
//#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
// 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
// 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
// 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
// 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
//
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPetHealthChanged, float, NewHealth);
//
//UCLASS()
//class PORTFOLIO_API UCPetAttributeSet : public UAttributeSet
//{
//	GENERATED_BODY()
//
//public:
//	UCPetAttributeSet();
//
//    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
//    virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
//
//    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
//	
//public:
//	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute", meta = (AllowPrivateAccess = true))
//	FGameplayAttributeData BaseHealth;
//	ATTRIBUTE_ACCESSORS(UCPetAttributeSet, BaseHealth);
//
//	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute", meta = (AllowPrivateAccess = true))
//	FGameplayAttributeData CurrentHealth;
//	ATTRIBUTE_ACCESSORS(UCPetAttributeSet, CurrentHealth);
//
//	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute", meta = (AllowPrivateAccess = true))
//	FGameplayAttributeData BaseDamage;
//	ATTRIBUTE_ACCESSORS(UCPetAttributeSet, BaseDamage);
//
//	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute", meta = (AllowPrivateAccess = true))
//	FGameplayAttributeData CurrentDamage;
//	ATTRIBUTE_ACCESSORS(UCPetAttributeSet, CurrentDamage);
//
//public:
//	FPetHealthChanged OnHealthChanged;
//};
