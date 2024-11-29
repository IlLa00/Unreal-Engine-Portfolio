#include "CEquipment.h"
#include "Global.h"

ACEquipment::ACEquipment()
{
	PrimaryActorTick.bCanEverTick = true;

	CheckNull(DataAsset);

	EquipWeapons[0] = DataAsset->Datas[0];

}

void ACEquipment::BeginPlay()
{
	Super::BeginPlay();

	if (!DataAsset)
	{
		PrintLine(); // TODO.. 데이터에셋이 안들어가있ㅇ므!!!!1
	}

	if(EquipWeapons[0].WeaponClass)
		CLog::Print(EquipWeapons[0].WeaponClass->GetName());

	if (EquipWeapons[0].AttributeClass)
	CLog::Print(EquipWeapons[0].AttributeClass->GetName());

	if(EquipWeapons[0].BaseDamage)
		CLog::Print(EquipWeapons[0].BaseDamage);

	if(EquipWeapons[0].BaseProficiency)
		CLog::Print(EquipWeapons[0].BaseProficiency);

	if(GetOwner())
		CLog::Print(GetOwner()->GetName());


}

void ACEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

