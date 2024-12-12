#include "Damage.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "GAS/Attribute/CMonsterAttributeSet.h"
#include "Pet/CPet.h"
#include "GAS/Attribute/CPetAttributeSet.h"

UDamage::UDamage()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

	FGameplayModifierInfo Modifier;
	Modifier.ModifierOp = EGameplayModOp::Additive;

	Modifiers.Add(Modifier);
}

void UDamage::SetModify(AActor* OwnerActor, AActor* OtherActor)
{
	if (OtherActor->IsA<ACEnemy>())
	{
		ACEnemy* Enemy = Cast<ACEnemy>(OtherActor);
		if (Enemy)
		{
			Modifiers[0].Attribute = Enemy->GetAttributeSet()->GetBaseHealthAttribute();

			ACPet* Pet = Cast<ACPet>(OwnerActor);
			if (Pet)
			{
				Modifiers[0].ModifierMagnitude = FScalableFloat((Pet->GetAttributeSet()->GetBaseDamage()) * -1);
			}
		}
	}
}