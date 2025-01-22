#include "CItem_Test.h"
#include "Global.h"
#include "Engine/DataTable.h"
#include "DataTable/CItemDataTable.h"
#include "Player/CPlayer.h"
#include "Inventory/CInventory.h"

ACItem_Test::ACItem_Test()
{
	CHelpers::GetAsset(&DataTable, "/Game/DataTable/DT_Item");
	CheckNull(DataTable);
}

void ACItem_Test::BeginPlay()
{
	Super::BeginPlay();

    TArray<FName> RowNames = DataTable->GetRowNames();
    for (const FName& RowName : RowNames)
    {
        FItemDataTable* Row = DataTable->FindRow<FItemDataTable>("NewRow", TEXT(""));
        if (Row)
        {
            ItemName = Row->Name;
            ItemTexture = Row->Texture;
        }
    }
}

void ACItem_Test::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->IsA<ACPlayer>())
    {
        ACPlayer* Player = Cast<ACPlayer>(OtherActor);
        Player->GetInventory()->AddItemToInventory(this);

        Destroy();
    }
}
