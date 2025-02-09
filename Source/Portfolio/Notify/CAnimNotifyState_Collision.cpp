#include "CAnimNotifyState_Collision.h"
#include "Global.h"
#include "Interface/CAttackCompInterface.h"
#include "Player/CPlayer.h"
#include "Equipment/CEquipment.h"
#include "Weapon/CWeapon.h"
#include "Components/BoxComponent.h"

void UCAnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (MeshComp->GetOwner()->GetClass()->ImplementsInterface(UCAttackCompInterface::StaticClass())) // 적군
	{
		ICAttackCompInterface* Owner = Cast<ICAttackCompInterface>(MeshComp->GetOwner());
		CheckNull(Owner);

		UBoxComponent* AttackComp = Owner->GetAttackComp();
		CheckNull(AttackComp);

		AttackComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else // 플레이어
	{
		ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());
		CheckNull(Player);

		ACEquipment* Equipment = Player->GetEquipment();
		CheckNull(Equipment);

		ACWeapon* Weapon = Equipment->GetCurrentCurrentEquipWeapon();
		CheckNull(Weapon);

		UBoxComponent* AttackComp = Weapon->GetAttackComp();
		CheckNull(AttackComp);

		AttackComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	
}

void UCAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (MeshComp->GetOwner()->GetClass()->ImplementsInterface(UCAttackCompInterface::StaticClass())) // 적군
	{
		ICAttackCompInterface* Owner = Cast<ICAttackCompInterface>(MeshComp->GetOwner());
		CheckNull(Owner);

		UBoxComponent* AttackComp = Owner->GetAttackComp();
		CheckNull(AttackComp);

		AttackComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else // 플레이어
	{
		ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());
		CheckNull(Player);

		ACEquipment* Equipment = Player->GetEquipment();
		CheckNull(Equipment);

		ACWeapon* Weapon = Equipment->GetCurrentCurrentEquipWeapon();
		CheckNull(Weapon);

		UBoxComponent* AttackComp = Weapon->GetAttackComp();
		CheckNull(AttackComp);

		AttackComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
