#include "CAnimInstance.h"
#include "Global.h"
#include "Player/CPlayer.h"

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* OwnerPawn = TryGetPawnOwner(); // 플레이어뿐만 아니라 움직이는 캐릭터 모두 사용해서 ACPlayer로 캐스팅x
	CheckNull(OwnerPawn);

	Speed = OwnerPawn->GetVelocity().Size2D();
	Direction = CalculateDirection(OwnerPawn->GetVelocity(), OwnerPawn->GetControlRotation()); 
}

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}