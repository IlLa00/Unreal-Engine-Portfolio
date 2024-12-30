#include "Spawner/CSpawner.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Enemy/CMonster.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enemy/CEnemyController.h"

ACSpawner::ACSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::GetClass(&MonsterClass, "/Game/Enemy/Monster/BP_CMonster");
	CheckNull(MonsterClass);

	Number = 5;
}

void ACSpawner::BeginPlay()
{
	Super::BeginPlay();

}

void ACSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACSpawner::Spawn(FVector PlayerLocation, FName PlayerArea)
{
	for (int32 i = 0; i < Number; i++) // 소환할 마릿수 만큼 반복
	{
		ACEnemyController* EnemyController = GetWorld()->SpawnActor<ACEnemyController>();
		CheckNull(EnemyController);

		FVector SpawnLocation = SetSpawnRange(PlayerLocation);
		FTransform SpawnTM = FTransform(FRotator(), SpawnLocation, FVector(1));

		ACMonster* Monster = GetWorld()->SpawnActorDeferred<ACMonster>(MonsterClass, SpawnTM);
		CheckNull(Monster);

		Monster->SetMesh(PlayerArea);
		EnemyController->Possess(Monster);

		Monster->FinishSpawning(SpawnTM);

		Monster->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));

	}
}

FVector ACSpawner::SetSpawnRange(FVector PlayerLocation)
{
	float Radius = 500.0f; // 예: 반지름 500 유닛 ////////// 나중에 공개변수로 열 것들
	float ZRange = 200.0f; // Z 축 범위: -200부터 +200 유닛

	// 랜덤 각도 계산 (0에서 360도 사이)
	float Angle = FMath::RandRange(0.0f, 2 * PI);

	// 원의 반지름 안에서 랜덤한 위치를 계산 (2D 평면에서)
	float XOffset = Radius * FMath::Cos(Angle);
	float YOffset = Radius * FMath::Sin(Angle);

	// Z 값을 랜덤으로 계산 (-ZRange ~ +ZRange)
	float ZOffset = FMath::RandRange(-ZRange, ZRange);

	// 3D 공간에서 랜덤 위치
	FVector RandomLocation = PlayerLocation + FVector(XOffset, YOffset, ZOffset);

	return RandomLocation;
}

