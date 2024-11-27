#include "CPlayer.h"
#include "Global.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/TriggerVolume.h"
#include "CGameModeBase.h"
#include "Blueprint/UserWidget.h" 
#include "Widget/CPlayerWidget.h"
#include "Camera/CameraComponent.h"
#include "Portal/CPortal.h"
#include "GAS/Attribute/CCharacterAttributeSet.h"
#include "GAS/GA/Summon.h"
#include "GAS/GA/Sprint.h"
#include "GAS/GE/Movement.h"

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
	CHelpers::CreateSceneComponent(this, &SpringArmComp, "SpringArmComp", GetMesh());
	CheckNull(SpringArmComp);

	SpringArmComp->TargetArmLength = 200.f;
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 150));
	SpringArmComp->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;

	CHelpers::CreateSceneComponent(this, &CameraComp, "CameraComp", SpringArmComp);
	CameraComp->SetRelativeLocation(FVector(0, 70, 0));

	GetCharacterMovement()->MaxWalkSpeed = 400.f; // 나중에 수정해야 함 이렇게 설정안할꺼임
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// Set AnimClass
	CHelpers::GetClass(&AnimClass, "/Game/Player/ABP_CPlayer");
	CheckNull(AnimClass);

	// Set WidgetClass
	CHelpers::GetClass(&WidgetClass, "/Game/Widget/BP_CPlayerWidget");
	CheckNull(WidgetClass);

	// Set GAS
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>("ASC");
	CheckNull(ASC);

	AttributeSet = CreateDefaultSubobject<UCCharacterAttributeSet>("AttributeSet");
	CheckNull(AttributeSet);

	/*CHelpers::GetClass(&BPMovementEffect, "/Game/GAS/BP_GE_Movement");
	CheckNull(BPMovementEffect);*/

	CHelpers::GetClass(&BPRegenerateStaminaEffect, "/Game/GAS/BP_GE_RegenerateStamina");
	CheckNull(BPRegenerateStaminaEffect);

}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetAnimClass(AnimClass);

	PlayerWidget = CreateWidget<UCPlayerWidget>(GetWorld(), WidgetClass);
	PlayerWidget->AddToViewport();

	OnActorBeginOverlap.AddDynamic(this, &ACPlayer::BeginOverlap);

	SetGAS();
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TagContainer.HasTag(FGameplayTag::RequestGameplayTag(FName("Character.State.Idle")))) // 아무것도 안하고 있을 때
	{
		if(AttributeSet->GetCurrentStamina() < AttributeSet->GetBaseStamina()) // 이 조건문 안걸면 디버그할때 보이는 화면과 다르게 스테미너가 좀더 차는거같음
			ASC->ApplyGameplayEffectSpecToSelf(*RegenerateStminaHandle.Data.Get()); // 저절로 스테미나가 참
	}
	else
	{
		//PrintLine(); // 일단 이렇게
	}
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput); // 수정할 예정, 옵션에서 설정가능하게
	PlayerInputComponent->BindAxis("Lookup", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ACPlayer::OnSprint); // 이것도 나중에 GAS로 관리할 수도 있음
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ACPlayer::OffSprint);

	PlayerInputComponent->BindAction("Summon", IE_Pressed, this, &ACPlayer::OnSummon);
}

UAbilitySystemComponent* ACPlayer::GetAbilitySystemComponent() const
{
	return ASC;
}

void ACPlayer::SetGAS()
{
	ASC->InitAbilityActorInfo(this, this); // 반드시 호출해야함 - 데이터 처리하는 오너와 아바타가 같음 

	SetGameplayAbility();
	SetGameplayEffect();
}

void ACPlayer::SetGameplayAbility()
{
	FGameplayAbilitySpec AbilitySpec(USummon::StaticClass()); 
	ASC->GiveAbility(AbilitySpec);

	FGameplayAbilitySpec SprintAbilitySpec(USprint::StaticClass());
	ASC->GiveAbility(SprintAbilitySpec);
}

void ACPlayer::SetGameplayEffect()
{
	FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();

	//MovementHandle = ASC->MakeOutgoingSpec(BPMovementEffect, 1.0f, EffectContext);
	RegenerateStminaHandle = ASC->MakeOutgoingSpec(BPRegenerateStaminaEffect, 1.0f, EffectContext);
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

void ACPlayer::OnSprint()
{
	if (!TagContainer.HasTag(FGameplayTag::RequestGameplayTag(FName("Character.Ability.Sprint"))))
	{
		TagContainer.RemoveTag(FGameplayTag::RequestGameplayTag(FName("Character.State.Idle")));

		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Ability.Sprint")));
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.State.Sprint")));
	}
	
	ASC->TryActivateAbility(ASC->FindAbilitySpecFromClass(USprint::StaticClass())->Handle);

	// ASC->ApplyGameplayEffectSpecToSelf(*MovementHandle.Data.Get());
}

void ACPlayer::OffSprint()
{
	if (TagContainer.HasTag(FGameplayTag::RequestGameplayTag(FName("Character.Ability.Sprint"))))
	{
		TagContainer.RemoveTag(FGameplayTag::RequestGameplayTag(FName("Character.Ability.Sprint")));
		TagContainer.RemoveTag(FGameplayTag::RequestGameplayTag(FName("Character.State.Sprint")));

		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.State.Idle")));
	}

	ASC->CancelAbilityHandle(ASC->FindAbilitySpecFromClass(USprint::StaticClass())->Handle);
}

void ACPlayer::OnSummon()
{
	if (!TagContainer.HasTag(FGameplayTag::RequestGameplayTag(FName("Character.Ability.Summon"))))
	{
		ASC->TryActivateAbility(ASC->FindAbilitySpecFromClass(USummon::StaticClass())->Handle);
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Ability.Summon")));
	}
	else
	{
		ASC->CancelAbilityHandle(ASC->FindAbilitySpecFromClass(USummon::StaticClass())->Handle);
		TagContainer.RemoveTag(FGameplayTag::RequestGameplayTag(FName("Character.Ability.Summon")));
	}
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

