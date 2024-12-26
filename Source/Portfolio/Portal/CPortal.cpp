#include "CPortal.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Blueprint/UserWidget.h" 
#include "Widget/CPortalWidget.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

ACPortal::ACPortal()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp");
	CheckNull(MeshComp);

	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Assets/Portal/Flat_Portal_v2_0_03_unwrapped_realigned_NOT_flipped_03");
	CheckNull(MeshAsset);

	MeshComp->SetSkeletalMesh(MeshAsset);
	MeshComp->SetRelativeScale3D(FVector(0.5f));

	CHelpers::CreateSceneComponent(this, &BoxComp, "BoxComp",MeshComp);
	CheckNull(BoxComp);

	BoxComp->SetCollisionProfileName("OverlapOnlyPawn");
	BoxComp->SetRelativeScale3D(FVector(10.f, 10.f, 1.f));

	CHelpers::CreateSceneComponent(this, &ParticleComp, "ParticleComp", MeshComp);
	CheckNull(ParticleComp);

	UParticleSystem* Asset;
	CHelpers::GetAsset(&Asset, "/Game/Assets/FXVarietyPack/Particles/P_ky_healAura");
	CheckNull(Asset);

	ParticleComp->SetTemplate(Asset);
	ParticleComp->SetRelativeScale3D(FVector(2.f));

	CHelpers::GetClass(&WidgetClass, "/Game/Widget/WB_CPortalWidget");
	CheckNull(WidgetClass);

}

void ACPortal::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACPortal::BeginOverlap);

	PortalWidget = CreateWidget<UCPortalWidget>(GetWorld(), WidgetClass);
	CheckNull(PortalWidget);

	PortalWidget->AddToViewport();
	PortalWidget->SetVisibility(ESlateVisibility::Hidden);
}

void ACPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPortal::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());

	ACharacter* Character = Cast<ACharacter>(OtherActor);
	CheckNull(Character);

	Character->GetCharacterMovement()->SetActive(false);

	PortalWidget->SetVisibility(ESlateVisibility::Visible);
	
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}

