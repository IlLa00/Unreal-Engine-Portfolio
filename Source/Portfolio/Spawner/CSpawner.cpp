#include "Spawner/CSpawner.h"
#include "Global.h"
#include "Enemy/CEnemy.h"

ACSpawner::ACSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	// GetWorld()->SpawnActorDeferred() <- 이거 써야할지 잘 생각해보자
	// FinishSpawning()
}

void ACSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACSpawner::Spawn(FVector PlayerLocation, FName PlayerArea)
{
	// 5마리 소환할꺼임

	// 여기서 실질적인 스폰을 해야하지않을까?
	// 지형에 따라(PlayerArea) /  플레이어 주변 몬스터(플레이어 위치에 따라 다른) / 랜덤 스폰.
	// 
	// 스피어 트레이스(플레이어위치가 루트) 범위 조정
	// 맵의 지형 확인 필요, 현재 여기가 사막인지 초원인지?
	// 무슨 몬스터를 소환할지.

	void SetSpawnRange(); // 플레이어 위치 알아야함, 이거 게임모드가 알려주자
	void SelectEnemy(); // 이건 
}

