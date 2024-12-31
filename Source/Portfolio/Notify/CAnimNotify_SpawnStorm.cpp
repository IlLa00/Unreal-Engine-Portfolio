#include "CAnimNotify_SpawnStorm.h"
#include "Global.h"
#include "Enemy/CBoss.h"
#include "Projectile/CStorm.h"

UCAnimNotify_SpawnStorm::UCAnimNotify_SpawnStorm()
{
	CHelpers::GetClass(&StormClass, "/Game/Projectile/BP_CStorm");
	CheckNull(StormClass);
}

FString UCAnimNotify_SpawnStorm::GetNotifyName() const
{
	return "SpawnStorm";
}

void UCAnimNotify_SpawnStorm::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACBoss* Boss = Cast<ACBoss>(MeshComp->GetOwner());
	CheckNull(Boss);

	FHitResult HitResult;
	FVector Start = Boss->GetActorLocation();
	FVector End = Start + FVector(0, 0, -10000.f);

	TArray<AActor*> Ignores;
	Ignores.Add(Boss);

	FActorSpawnParameters Params;
	Params.Owner = Boss;
	
	if (UKismetSystemLibrary::LineTraceSingleByProfile(GetWorld(), Start, End, "BlockAll", true, Ignores, EDrawDebugTrace::Persistent, HitResult, true))
	{
		GetWorld()->SpawnActor<ACStorm>(StormClass, HitResult.Location + FVector(0, 0, 300), Boss->GetActorForwardVector().Rotation(), Params);
	}
}
