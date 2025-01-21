#include "CItem_Test.h"
#include "Global.h"
#include "Engine/DataTable.h"

ACItem_Test::ACItem_Test()
{
	CHelpers::GetAsset(&DataTable, "/Game/DataTable/DT_Item");
	CheckNull(DataTable);
}

void ACItem_Test::BeginPlay()
{
	Super::BeginPlay();

	TArray<FName> RowNames = DataTable->GetRowNames();

	for (FName Name : RowNames)
	{
		CLog::Print(Name.ToString());
	}

}

void ACItem_Test::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}
