#include "CItem_HealBuff.h"
#include "Global.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Player/CPlayer.h"
#include "GAS/Attribute/CCharacterAttributeSet.h"
#include "DataAsset/CItemDataAsset.h"
#include "AbilitySystemBlueprintLibrary.h"

ACItem_HealBuff::ACItem_HealBuff()
{
	CHelpers::CreateSceneComponent(this, &NiagaraComp, "NiagaraComp", RootGravityComp);
	CheckNull(NiagaraComp);

	CHelpers::GetClass(&BPHealEffect, "/Game/GAS/BP_GE_Heal");
	CheckNull(BPHealEffect);
}

void ACItem_HealBuff::BeginPlay()
{
	Super::BeginPlay();

	for (const auto& Data : DataAsset->Datas)
	{
		if (GetClass() == Data.Item)
		{
			Value = Data.Value;
			break;
		}
	}

	FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();

	HealHandle = ASC->MakeOutgoingSpec(BPHealEffect, 1.0f, EffectContext);
}
	
void ACItem_HealBuff::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACPlayer* Player = Cast<ACPlayer>(OtherActor);
	CheckNull(Player);
	CheckNull(Player->GetAbilitySystemComponent());

	CheckNull(ASC);

	ASC->ApplyGameplayEffectSpecToTarget(*HealHandle.Data.Get(), Player->GetAbilitySystemComponent());

	Destroy();
}
