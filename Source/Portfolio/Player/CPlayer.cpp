#include "CPlayer.h"
#include "Global.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Portal/CPortal.h"
#include "Engine/TriggerVolume.h"
#include "CGameModeBase.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set SkeletalMesh
	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Assets/CR/LQ/Modular_001_Bergs10/Mesh/SKM_Bergs10_1");
	CheckNull(MeshAsset);
	
	GetMesh()->SetSkeletalMesh(MeshAsset);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	// Set Components
	CHelpers::CreateSceneComponent(this, &SpringArmComp, "SpringArmComp",GetMesh());
	CheckNull(SpringArmComp);

	SpringArmComp->TargetArmLength = 200.f;
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 150));
	SpringArmComp->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;

	CHelpers::CreateSceneComponent(this, &CameraComp, "CameraComp",SpringArmComp);
	CameraComp->SetRelativeLocation(FVector(0, 70, 0));

	GetCharacterMovement()->MaxWalkSpeed = 400.f; // 나중에 수정해야 함 이렇게 설정안할꺼임
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->bOrientRotationToMovement = true; 

	// Set AnimClass;
	CHelpers::GetClass(&AnimClass,"/Game/Player/ABP_CPlayer");
	CheckNull(AnimClass);

	GetMesh()->SetAnimClass(AnimClass);

	//Todo. 점프 + 앉기 + 슬라이딩기능 추가해보기.

		
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACPlayer::BeginOverlap);
	
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput); // 수정할 예정, 옵션에서 설정가능하게
	PlayerInputComponent->BindAxis("Lookup", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ACPlayer::OnSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ACPlayer::OffSprint);
}

void ACPlayer::OnMoveForward(float Axis)
{
	FRotator ControlRot = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction = FQuat(ControlRot).GetForwardVector();

	AddMovementInput(Direction, Axis);
}

void ACPlayer::OnMoveRight(float Axis)
{
	FRotator ControlRot = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction = FQuat(ControlRot).GetRightVector();

	AddMovementInput(Direction, Axis);
}

void ACPlayer::OnTurn(float Axis)
{

}

void ACPlayer::OnLookUp(float Axis)
{

}

void ACPlayer::OnSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void ACPlayer::OffSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
}

void ACPlayer::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor == Cast<ACPortal>(OtherActor)) // 포탈과 부딪히면
		GetCharacterMovement()->StopMovementImmediately(); // 이거 bCanMove 만들어서 제어하자.

	if (OtherActor->IsA(ATriggerVolume::StaticClass())) // 트리거 볼륨에 부딪히면 !만약에 액터태그 관리해야 하면 여기서 for문걸기
	{
		ACGameModeBase* MyGameMode = Cast<ACGameModeBase>(GetWorld()->GetAuthGameMode());
		CheckNull(MyGameMode);
		
		MyGameMode->SetPlayerArea(OtherActor);
	}
}

