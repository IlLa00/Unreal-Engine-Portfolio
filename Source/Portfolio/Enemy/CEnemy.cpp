#include "CEnemy.h"
#include "Global.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "Components/TextRenderComponent.h"
#include "NavigationInvokerComponent.h"
#include "Components/WidgetComponent.h"
#include "DataAsset/CMonsterMeshDataAsset.h"
#include "GAS/Attribute/CAIAttributeSet.h"
#include "CEnemyController.h"
#include "GAS/GA/AI_Attack.h"
#include "GAS/GA/AI_GetHit.h"
#include "GAS/GA/AI_Dead.h"
#include "Player/CPlayer.h"
#include "GAS/Attribute/CCharacterAttributeSet.h"
#include "Widget/CDamageWidget.h"

ACEnemy::ACEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &TextComp, "TextComp", GetMesh());
	CheckNull(TextComp);

	TextComp->SetRelativeLocation(FVector(0, 0, 200));
	TextComp->SetRelativeRotation(FRotator(0, 90, 0));
	TextComp->SetHorizontalAlignment(EHTA_Center);

	CHelpers::CreateSceneComponent(this, &DamageTextComp, "DamageTextComp", GetMesh());
	CheckNull(DamageTextComp);

	CHelpers::CreateActorComponent(this, &InvokerComp, "InvokerComp");
	CheckNull(InvokerComp);

	CHelpers::GetClass(&DamageWidgetClass, "/Game/Widget/WB_CDamageWidget");
	CheckNull(DamageWidgetClass);

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>("ASC");
	CheckNull(ASC);

	AIAttribute = CreateDefaultSubobject<UCAIAttributeSet>("AIAttribute");
	CheckNull(AIAttribute);

}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ACEnemyController::StaticClass();

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

	if (DamageTextComp)
	{
		DamageTextComp->SetWidgetClass(DamageWidgetClass);
		DamageTextComp->RegisterComponent();
		DamageTextComp->SetWorldLocation(GetActorLocation());
		DamageTextComp->SetVisibility(true);
	}

	if (ASC)
	{
		ASC->InitAbilityActorInfo(this, this);

		FGameplayAbilitySpec AttackSpec(UAI_Attack::StaticClass());
		ASC->GiveAbility(AttackSpec);

		FGameplayAbilitySpec HitSpec(UAI_GetHit::StaticClass());
		ASC->GiveAbility(HitSpec);

		FGameplayAbilitySpec DeadSpec(UAI_Dead::StaticClass());
		ASC->GiveAbility(DeadSpec);
	}
	
	TagContainer.AddTag(FGameplayTag::RequestGameplayTag("AI.State.Idle"));

	if(AIAttribute)
		AIAttribute->OnDamaged.AddDynamic(this, &ACEnemy::SetDamageText);
}

void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TagContainer.Num() > 0)
	{
		for (const FGameplayTag& Tag : TagContainer)
		{
			TextComp->SetText(FText::FromString(Tag.ToString()));
		}
	}
}

UAbilitySystemComponent* ACEnemy::GetAbilitySystemComponent() const
{
	return ASC;
}

void ACEnemy::SetDamageText(float NewValue)
{
	CheckNull(DamageTextComp->GetWidget());

	UCDamageWidget* Widget = Cast<UCDamageWidget>(DamageTextComp->GetWidget());
	CheckNull(Widget);

	DamageTextComp->SetVisibility(true);

	Widget->SetDamageText(NewValue);

	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,&ACEnemy::HiddenDamage, 1.f, false);
}

void ACEnemy::HiddenDamage()
{
	PrintLine();
	DamageTextComp->SetVisibility(false);
}

void ACEnemy::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}
