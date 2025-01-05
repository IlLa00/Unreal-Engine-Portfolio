#include "CGameModeBase.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "AbilitySystemGlobals.h"
#include "Spawner/CSpawner.h"
#include "Engine/TriggerVolume.h"
#include "Engine/TargetPoint.h"

ACGameModeBase::ACGameModeBase()
{
	UAbilitySystemGlobals::Get().InitGlobalData();

	// Set DefaultPawnClass
	TSubclassOf<ACPlayer> PlayerClass;
	CHelpers::GetClass(&PlayerClass, "/Script/Engine.Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'");
	CheckNull(PlayerClass);

	DefaultPawnClass = PlayerClass;

	CHelpers::GetClass(&SpawnerClass, "/Game/Spawner/BP_CSpawner");
	CheckNull(SpawnerClass);
	
}

void ACGameModeBase::BeginPlay()
{
	PlayerArea = "Grasslands"; // 플레이어지역 초기 설정, 하드코딩 불편
	
	FVector SpawnLocation = FVector(0, 0, 0); // 기본 위치로 설정
	FRotator SpawnRotation = FRotator::ZeroRotator; // 회전은 기본값

	Spawner = GetWorld()->SpawnActor<ACSpawner>(SpawnerClass, SpawnLocation, SpawnRotation);
	CheckNull(Spawner);

	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &ACGameModeBase::Spawn, 5.f, true); // 5초마다 스폰함수 실행

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), TargetPointActors);
	
	for (const auto& Actor : TargetPointActors)
	{
		for (const auto& Tag : Actor->Tags)
		{
			TargetPointName->Append(Tag.ToString());
		}
	}
}

void ACGameModeBase::Spawn()
{
	ACPlayer* Player = Cast<ACPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	CheckNull(Player);

	Spawner->Spawn(Player->GetActorLocation(), PlayerArea);
}

void ACGameModeBase::Teleport(FName Area)
{
	for (const auto& Actor : TargetPointActors)
	{
		if (Area == Actor->Tags[0])
		{
			ACPlayer* Player = Cast<ACPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
			CheckNull(Player); // 여기가 안됨

			/*
			if (Player->GetMesh()->IsSimulatingPhysics())
			{
				Player->GetMesh()->SetSimulatePhysics(false);
				PrintLine();
			}
			*/
			if (!(Player->GetMesh()->GetCollisionProfileName() == FName("CharacterMesh")))
			{
				Player->GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));
				PrintLine();
			}

			Player->SetActorLocation(Actor->GetActorLocation());
			Player->GetMesh()->UpdateComponentToWorld();

			PlayerArea = Actor->Tags[0];

			break;
		}
	}
}

void ACGameModeBase::SetPlayerArea(AActor* OtherActor) // 플레이어 지역 바꾸기
{
	for (const auto& MyTags : OtherActor->Tags)
		PlayerArea = MyTags;

	CLog::Print(PlayerArea.ToString());
}
