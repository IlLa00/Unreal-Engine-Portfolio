#include "CAnimNotifyState_Collision.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Components/BoxComponent.h"

void UCAnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	ACEnemy* Enemy = Cast<ACEnemy>(MeshComp->GetOwner());
	CheckNull(Enemy);

	Enemy->GetAttackComp()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

}

void UCAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	ACEnemy* Enemy = Cast<ACEnemy>(MeshComp->GetOwner());
	CheckNull(Enemy);

	Enemy->GetAttackComp()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
