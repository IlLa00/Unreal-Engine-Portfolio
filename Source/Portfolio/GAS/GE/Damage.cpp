#include "Damage.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "GAS/Attribute/CMonsterAttributeSet.h"
#include "Pet/CPet.h"
#include "GAS/Attribute/CPetAttributeSet.h"

UDamage::UDamage()
{
	
}

void UDamage::SetModify(AActor* OwnerActor, AActor* OtherActor)
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

	FGameplayModifierInfo Modifier;
	Modifier.ModifierOp = EGameplayModOp::Additive;

	if (OtherActor->IsA<ACEnemy>())
	{
		ACEnemy* Enemy = Cast<ACEnemy>(OtherActor);
		if (Enemy)
		{
			Modifier.Attribute = Enemy->GetAttributeSet()->GetCurrentHealthAttribute();

			ACPet* Pet = Cast<ACPet>(OwnerActor);
			if (Pet)
			{
				Modifier.ModifierMagnitude = FScalableFloat((Pet->GetAttributeSet()->GetCurrentDamage()) * -1);
				Modifiers.Add(Modifier);
			}
		}
	}
}