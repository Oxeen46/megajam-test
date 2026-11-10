#include "EnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	Stats = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats"));
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	Stats->OnDied.AddDynamic(this, &AEnemyCharacter::HandleDeath);
}

void AEnemyCharacter::HandleDeath(AActor* DeadActor)
{
	GetCharacterMovement()->DisableMovement();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);
	SetLifeSpan(5.f);
}