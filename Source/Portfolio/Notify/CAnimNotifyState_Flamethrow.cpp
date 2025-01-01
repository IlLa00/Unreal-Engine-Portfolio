#include "CAnimNotifyState_Flamethrow.h"
#include "Global.h"
#include "Enemy/CBoss.h"
#include "Player/CPlayer.h"
#include "GAS/Attribute/CCharacterAttributeSet.h"

void UCAnimNotifyState_Flamethrow::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	ACBoss* Boss = Cast<ACBoss>(MeshComp->GetOwner());
	CheckNull(Boss);

	FVector Start = Boss->GetMesh()->GetSocketLocation("Jaw01") + Boss->GetActorForwardVector() * 500.f;
	FVector End = Start;

	TArray<AActor*> Ignores;
	FHitResult HitResult;

	if (UKismetSystemLibrary::SphereTraceSingleByProfile(Boss->GetWorld(), Start, End, 200.f, "Pawn", false, Ignores, EDrawDebugTrace::ForDuration, HitResult, true))
	{
		ACPlayer* Player = Cast<ACPlayer>(HitResult.GetActor());
		CheckNull(Player);

		Player->GetAttributeSet()->SetCurrentHealth(Player->GetAttributeSet()->GetCurrentHealth() - 5.f); // 틱함수라 바로 공격력적용하면 너무쎌 것 같음
	}
}


