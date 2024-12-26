#include "CEnemy.h"
#include "Global.h"
#include "AbilitySystemComponent.h"
#include "Components/WidgetComponent.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "Components/TextRenderComponent.h"
#include "Components/BoxComponent.h"
#include "DataAsset/CMonsterMeshDataAsset.h"
#include "GAS/Attribute/CMonsterAttributeSet.h"
#include "CEnemyController.h"
#include "GAS/GA/AI_Attack.h"
#include "GAS/GA/AI_GetHit.h"
#include "GAS/GA/AI_Dead.h"
#include "Widget/CEnemyHealthWidget.h"
#include "Player/CPlayer.h"
#include "GAS/Attribute/CCharacterAttributeSet.h"

ACEnemy::ACEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &TextComp, "TextComp", GetMesh());
	CheckNull(TextComp);

	TextComp->SetRelativeLocation(FVector(0, 0, 200));
	TextComp->SetRelativeRotation(FRotator(0, 90, 0));
	TextComp->SetHorizontalAlignment(EHTA_Center);

	CHelpers::CreateSceneComponent(this, &AttackComp, "AttackComp", GetMesh());
	CheckNull(AttackComp);
	
	CHelpers::CreateSceneComponent(this, &HealthWidgetComp, "HealthWidgetComp", GetMesh());

	TSubclassOf<UCEnemyHealthWidget> HealthWidgetClass;
	CHelpers::GetClass(&HealthWidgetClass, "/Game/Widget/WB_CEnemyHealthWidget");
	HealthWidgetComp->SetWidgetClass(HealthWidgetClass);
	HealthWidgetComp->SetRelativeLocation(FVector(0, 0, 190));
	HealthWidgetComp->SetDrawSize(FVector2D(120, 20));
	HealthWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>("ASC");
	CheckNull(ASC);

	CHelpers::GetAsset(&DataAsset, "/Game/DataAsset/DA_Monster");
	CheckNull(DataAsset);

	Attribute = CreateDefaultSubobject<UCMonsterAttributeSet>("Attribute");
	CheckNull(Attribute);

}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ACEnemyController::StaticClass();

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

	if (AttackComp)
	{
		AttackComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "AttackSocket");
		AttackComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		AttackComp->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy::BeginOverlap);
	}

	HealthWidgetComp->InitWidget();
	HealthWidgetObject = Cast<UCEnemyHealthWidget>(HealthWidgetComp->GetUserWidgetObject());
	if (HealthWidgetObject)
		HealthWidgetObject->Update(Attribute->GetCurrentHealth(), Attribute->GetBaseHealth());

	ASC->InitAbilityActorInfo(this, this);

	FGameplayAbilitySpec AttackSpec(UAI_Attack::StaticClass());
	ASC->GiveAbility(AttackSpec);

	FGameplayAbilitySpec HitSpec(UAI_GetHit::StaticClass());
	ASC->GiveAbility(HitSpec);

	FGameplayAbilitySpec DeadSpec(UAI_Dead::StaticClass());
	ASC->GiveAbility(DeadSpec);

	TagContainer.AddTag(FGameplayTag::RequestGameplayTag("AI.State.Idle"));

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

void ACEnemy::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<ACEnemy>())
		return;

	if (OtherActor->IsA<ACPlayer>())
	{
		ACPlayer* Player = Cast<ACPlayer>(OtherActor);
		CheckNull(Player);

		Player->GetAttributeSet()->SetCurrentHealth(Player->GetAttributeSet()->GetCurrentHealth() - GetAttributeSet()->GetCurrentDamage());
	}
}
