#include "CItem_HealBuff.h"
#include "Global.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Player/CPlayer.h"
#include "GAS/Attribute/CCharacterAttributeSet.h"
#include "DataAsset/CItemDataAsset.h"

ACItem_HealBuff::ACItem_HealBuff()
{
	CHelpers::CreateSceneComponent(this, &NiagaraComp, "NiagaraComp", RootGravityComp);
	CheckNull(NiagaraComp);
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
}
	
void ACItem_HealBuff::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OverlapParitcle)
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), OverlapParitcle, OtherActor->GetActorLocation());

	ACPlayer* Player = Cast<ACPlayer>(OtherActor);
	CheckNull(Player);

	Player->GetAttributeSet()->SetCurrentHealth(Player->GetAttributeSet()->GetCurrentHealth() + Value); // 나중에 데이터로 바꾸기

	Destroy();
}
