#include "CGameModeBase.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "AbilitySystemGlobals.h"
#include "Spawner/CSpawner.h"
#include "Engine/TriggerVolume.h"

ACGameModeBase::ACGameModeBase()
{
	UAbilitySystemGlobals::Get().InitGlobalData();

	// Set DefaultPawnClass
	TSubclassOf<ACPlayer> PlayerClass;
	CHelpers::GetClass(&PlayerClass, "/Script/Engine.Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'");
	CheckNull(PlayerClass);

	DefaultPawnClass = PlayerClass;
	
}

void ACGameModeBase::BeginPlay()
{
	TArray<AActor*, FDefaultAllocator> Areas;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATriggerVolume::StaticClass(), Areas); // 월드에 배치된 트리거들 가져오기
	if (Areas.Num() < 0) return;

	for (const auto& Area : Areas)
	{
		AActor* PlayerStart = FindPlayerStart(GetWorld()->GetFirstPlayerController())z;
		CheckNull(PlayerStart);

		if (PlayerStart->IsOverlappingActor(Area)) // 플레이어 스타트가 있는 지역 초기화
		{
			SetPlayerArea(Area);
			CLog::Print(Area->GetName());
			break;
		}
	}
	
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &ACGameModeBase::Spawn, 5.f, true); // 5초마다 스폰함수 실행
}

void ACGameModeBase::Spawn()
{
	ACPlayer* Player = Cast<ACPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	CheckNull(Player);

	Spawner->Spawn(Player->GetActorLocation(), PlayerArea);
}

void ACGameModeBase::Teleport()
{
	// 나중에 구현
}

void ACGameModeBase::SetPlayerArea(AActor* OtherActor) // 플레이어 지역 바꾸기
{
	for (const auto& MyTags : OtherActor->Tags)
		PlayerArea = MyTags;

	CLog::Print(PlayerArea.ToString());
}
