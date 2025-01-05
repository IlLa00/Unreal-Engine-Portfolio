#include "CPlayer.h"
#include "Global.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/TriggerVolume.h"
#include "Components/TextRenderComponent.h"
#include "CGameModeBase.h"
#include "Blueprint/UserWidget.h" 
#include "Widget/CPlayerWidget.h"
#include "Widget/CDeathWidget.h"
#include "Camera/CameraComponent.h"
#include "Portal/CPortal.h"
#include "GAS/Attribute/CCharacterAttributeSet.h"
#include "GAS/GA/Summon.h"
#include "GAS/GA/Sprint.h"
#include "GAS/GA/Jump.h"
#include "Equipment/CEquipment.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

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

	CHelpers::CreateSceneComponent(this, &TextComp, "TextComp", GetMesh());
	CheckNull(TextComp);

	TextComp->SetRelativeLocation(FVector(0, 0, 200));
	TextComp->SetRelativeRotation(FRotator(0, -90, 0));
	TextComp->SetHorizontalAlignment(EHTA_Center);

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

	CHelpers::GetClass(&BPRegenerateStaminaEffect, "/Game/GAS/BP_GE_RegenerateStamina");
	CheckNull(BPRegenerateStaminaEffect);

	CHelpers::GetClass(&EquipmentClass, "/Game/Equipment/BP_CEquipment");
	CheckNull(EquipmentClass);

	CHelpers::GetClass(&DeathWidgetClass, "/Game/Widget/WB_CDeathWidget");
	CheckNull(DeathWidgetClass);

	TeamId = 0;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetAnimClass(AnimClass);

	PlayerWidget = CreateWidget<UCPlayerWidget>(GetWorld(), WidgetClass);
	CheckNull(PlayerWidget);

	PlayerWidget->AddToViewport();

	OnActorBeginOverlap.AddDynamic(this, &ACPlayer::BeginOverlap);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	Equipment = GetWorld()->SpawnActor<ACEquipment>(EquipmentClass, SpawnParams);
	CheckNull(Equipment);

	if (ASC)
	{
		ASC->InitAbilityActorInfo(this, this); // 반드시 호출해야함 
		SetGAS();
	}

	DeathWidget = CreateWidget<UCDeathWidget>(GetWorld(), DeathWidgetClass);
	CheckNull(DeathWidget);

	DeathWidget->AddToViewport();
	DeathWidget->SetVisibility(ESlateVisibility::Hidden);
}

FGenericTeamId ACPlayer::GetGenericTeamId() const
{
	return FGenericTeamId(TeamId);
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
		// PrintLine(); // 일단 이렇게
	}

	if (TagContainer.Num() > 0)
	{
		for (const FGameplayTag& Tag : TagContainer)
		{
			TextComp->SetText(FText::FromString(Tag.ToString()));
		}
	}
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput); // todo.. 수정할 예정, 옵션에서 설정가능하게
	PlayerInputComponent->BindAxis("Lookup", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ACPlayer::OnSprint); 
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ACPlayer::OffSprint);

	PlayerInputComponent->BindAction("Summon", IE_Pressed, this, &ACPlayer::OnSummon);

	PlayerInputComponent->BindAction("EquipFirstSlot", IE_Pressed, this, &ACPlayer::OnEquipFirstSlot);
	PlayerInputComponent->BindAction("EquipSecondSlot", IE_Pressed, this, &ACPlayer::OnEquipSecondSlot);
	PlayerInputComponent->BindAction("EquipThirdSlot", IE_Pressed, this, &ACPlayer::OnEquipThirdSlot);
	PlayerInputComponent->BindAction("EquipLastSlot", IE_Pressed, this, &ACPlayer::OnEquipLastSlot);

	PlayerInputComponent->BindAction("MainAction", IE_Pressed, this, &ACPlayer::OnMainAction);
	PlayerInputComponent->BindAction("MainAction", IE_Released, this, &ACPlayer::OffMainAction);

	PlayerInputComponent->BindAction("SubAction", IE_Pressed, this, &ACPlayer::OnSubAction);
	PlayerInputComponent->BindAction("SubAction", IE_Released, this, &ACPlayer::OffSubAction);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ACPlayer::OnReload);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACPlayer::OnJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACPlayer::OffJump);
}

UAbilitySystemComponent* ACPlayer::GetAbilitySystemComponent() const
{
	return ASC;
}

void ACPlayer::SetGAS()
{
	SetGameplayAbility();
	SetGameplayEffect();
}

void ACPlayer::SetGameplayAbility()
{
	FGameplayAbilitySpec AbilitySpec(USummon::StaticClass()); 
	ASC->GiveAbility(AbilitySpec);

	FGameplayAbilitySpec SprintAbilitySpec(USprint::StaticClass());
	ASC->GiveAbility(SprintAbilitySpec);

	FGameplayAbilitySpec JumpAbilitySpec(UJump::StaticClass());
	ASC->GiveAbility(JumpAbilitySpec);
}

void ACPlayer::SetGameplayEffect()
{
	FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();

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
	
	ASC->TryActivateAbility(ASC->FindAbilitySpecFromClass(USprint::StaticClass())->Handle); // todo.. 스테미너 조건 검사
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

void ACPlayer::OnEquipFirstSlot()
{
	Equipment->Equip(1);
}

void ACPlayer::OnEquipSecondSlot()
{
	Equipment->Equip(2);
}

void ACPlayer::OnEquipThirdSlot()
{
	Equipment->Equip(3);
}

void ACPlayer::OnEquipLastSlot()
{
	Equipment->Equip(4);
}

void ACPlayer::OnMainAction()
{
	SetUsePawnControlRotation(false); //  todo.. 아무것도 안들때도 되어버림
	Equipment->OnMainAction();
}

void ACPlayer::OffMainAction()
{
	SetUsePawnControlRotation(true);
	Equipment->OffMainAction();
}

void ACPlayer::OnSubAction()
{
	Equipment->OnSubAction();
}

void ACPlayer::OffSubAction()
{
	Equipment->OffSubAction();
}

void ACPlayer::OnReload()
{
	Equipment->Reload();
}

void ACPlayer::OnJump()
{
	if (!GetCharacterMovement()->IsFalling())
	{
		ASC->TryActivateAbility(ASC->FindAbilitySpecFromClass(UJump::StaticClass())->Handle);
	}
}

void ACPlayer::OffJump()
{
	ASC->CancelAbilityHandle(ASC->FindAbilitySpecFromClass(USummon::StaticClass())->Handle);
}

void ACPlayer::ShowDeathWidget()
{
	GetController<APlayerController>()->SetInputMode(FInputModeUIOnly());

	DeathWidget->SetVisibility(ESlateVisibility::Visible);

	GetController<APlayerController>()->SetShowMouseCursor(true);

	PrintLine();

	GetWorld()->GetTimerManager().ClearTimer(WidgetHandle);
}

void ACPlayer::Death()
{
	// 위젯 변화 모든 위젯끄기
	ASC->CancelAllAbilities();

	//GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	//GetMesh()->UpdateComponentToWorld();

	GetController<APlayerController>()->SetInputMode(FInputModeUIOnly());

	TArray<UUserWidget*> Widgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), Widgets, UUserWidget::StaticClass());

	for (auto& Widget : Widgets)
	{
		Widget->SetVisibility(ESlateVisibility::Hidden);
	}

	GetWorld()->GetTimerManager().SetTimer(WidgetHandle, this, &ACPlayer::ShowDeathWidget, 3.f, false);
}

void ACPlayer::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor == Cast<ACPortal>(OtherActor)) 
		GetCharacterMovement()->StopMovementImmediately(); // todo.. 이거 의미있는지?

	if (OtherActor->IsA(ATriggerVolume::StaticClass())) 
	{
		ACGameModeBase* MyGameMode = Cast<ACGameModeBase>(GetWorld()->GetAuthGameMode());
		CheckNull(MyGameMode);

		MyGameMode->SetPlayerArea(OtherActor);
	}
}

void ACPlayer::SetUsePawnControlRotation(bool bUse)
{
	if (bUse)
		bUseControllerRotationYaw = false;
	else
		bUseControllerRotationYaw = true;
}

