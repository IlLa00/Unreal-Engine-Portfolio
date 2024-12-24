#include "CItem_HealBuff.h"
#include "Global.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

ACItem_HealBuff::ACItem_HealBuff()
{

}

void ACItem_HealBuff::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PrintLine(); // 잘들어옴 이제 어트리뷰트 조작하면됨.

	// 맞은 대상에게 파티클 재생
	if(SpawnParticle)
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SpawnParticle, OtherActor->GetActorLocation());

	Destroy();
}
