#include "CAnimNotify_SpawnProjectile.h"
#include "Global.h"
#include "Projectile/CProjectile.h"
#include "GameFramework/Character.h"

UCAnimNotify_SpawnProjectile::UCAnimNotify_SpawnProjectile()
{
	CHelpers::GetClass(&ProjectileClass, "/Game/Projectile/BP_CProjectile");
	CheckNull(ProjectileClass);
}

FString UCAnimNotify_SpawnProjectile::GetNotifyName() const
{
	return "SpawnProjectile";
}

void UCAnimNotify_SpawnProjectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(ProjectileClass);

	ACharacter* OwnerCharacter = Cast<ACharacter>(MeshComp->GetOwner());
	if (OwnerCharacter)
	{
		FTransform SpawnTM;
		SpawnTM.SetLocation(OwnerCharacter->GetMesh()->GetSocketLocation("WeaponSocket"));
		SpawnTM.SetRotation(FQuat(OwnerCharacter->GetActorForwardVector().Rotation()));

		FActorSpawnParameters SpawnParam;
		SpawnParam.Owner = OwnerCharacter;

		MeshComp->GetOwner()->GetWorld()->SpawnActor<ACProjectile>(ProjectileClass, SpawnTM, SpawnParam);
	}

}
