#include "CAnimInstance.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Player/CPlayer.h"
#include "Enemy/CEnemy.h"
#include "Enemy/CBoss.h"

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner()); 
	CheckNull(OwnerCharacter);

	Speed = OwnerCharacter->GetVelocity().Size2D();
	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());

	if (OwnerCharacter->IsA<ACBoss>())
	{
		ACBoss* Boss = Cast<ACBoss>(OwnerCharacter);
		if (Boss)
		{
			FlyingSpeed = Boss->GetFloatingComp()->MaxSpeed;
		}
	}

	if (Cast<ACPlayer>(OwnerCharacter))
	{
		ACPlayer* Player = Cast<ACPlayer>(OwnerCharacter);

		TagContainer = Player->GetTagContainer();
	}
	else if (Cast<ACEnemy>(OwnerCharacter))
	{
		ACEnemy* Enemy = Cast<ACEnemy>(OwnerCharacter);

		TagContainer = Enemy->GetTagContainer();
	}

	IsFall = OwnerCharacter->GetCharacterMovement()->IsFalling();

	Pitch = TryGetPawnOwner()->GetBaseAimRotation().Pitch;
}

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}