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

    UStaticMesh* MeshAsset;
    CHelpers::GetAsset(&MeshAsset, "/Game/Lowpoly_Objects_Pack/backpack");
    CheckNull(MeshAsset);

    CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp", RootComponent);
    CheckNull(MeshComp);

    MeshComp->SetStaticMesh(MeshAsset);

    Count = 1;
}

void ACItem_Test::BeginPlay()
{
	Super::BeginPlay();

    TArray<FName> DTRowNames = DataTable->GetRowNames();

    int32 Index = FMath::RandRange(0, DTRowNames.Num() - 1);

    FItemDataTable* Row = DataTable->FindRow<FItemDataTable>(DTRowNames[Index], TEXT(""));

    ItemName = Row->Name;
    ItemTexture = Row->Texture;
}

void ACItem_Test::IncreaseCount()
{
    Count++;
}

void ACItem_Test::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->IsA<ACPlayer>())
    {
        ACPlayer* Player = Cast<ACPlayer>(OtherActor);
        CheckNull(Player);
        CheckNull(Player->GetInventory());

        Player->GetInventory()->AddItemToInventory(this);

        Destroy();
    }
}
