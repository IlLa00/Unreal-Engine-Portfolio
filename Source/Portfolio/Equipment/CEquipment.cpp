#include "CEquipment.h"
#include "Global.h"
#include "GameFramework/Character.h"

ACEquipment::ACEquipment()
{
	PrimaryActorTick.bCanEverTick = true;

	
}

void ACEquipment::BeginPlay()
{
	Super::BeginPlay();

	CheckNull(DataAsset);
	
	//EquipWeapons[0] = DataAsset->Datas[0];

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	CheckNull(OwnerCharacter);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = OwnerCharacter;

	EquipWeapon[0] = OwnerCharacter->GetWorld()->SpawnActor<ACWeapon>(DataAsset->Datas[0].WeaponClass,SpawnParams);
	CheckNull(EquipWeapon[0]);

	EquipWeapon[0]->SetActorHiddenInGame(true);


}

void ACEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACEquipment::Equip(int32 slot)
{
	CheckNull(Montage);

	// 장착 몽타주 재생
	OwnerCharacter->PlayAnimMontage(Montage);
	
	// 위젯 변화

	// 무기 장착중인지 아닌지?
}

void ACEquipment::Begin_Equip()
{
	// 무기 손 소켓에 붙이기
	EquipWeapon[0]->SetActorHiddenInGame(false);

	EquipWeapon[0]->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "hand_r");
}

void ACEquipment::End_Equip()
{
	// 능력 장착
}

