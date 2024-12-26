#include "CItem_HealBuff.h"
#include "Global.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

ACItem_HealBuff::ACItem_HealBuff()
{

}

void ACItem_HealBuff::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CLog::Print(OtherComp->GetName()); // 브러쉬 컴포넌트랑 부딪히는데 이게뭐임???????????

	// 맞은 대상에게 파티클 재생
	if(SpawnParticle)
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SpawnParticle, OtherActor->GetActorLocation());

	Destroy();
}
