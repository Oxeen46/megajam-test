#include "MyProjectCharacter.h"
#include "PlayerHUDWidget.h"
#include "StatsComponent.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "DrawDebugHelpers.h"
#include "Engine/OverlapResult.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "MyProject.h"
#include "EngineUtils.h"
#include "EnemyCharacter.h"
#include "Engine/Engine.h"
#include "CommandMenuWidget.h"
#include "Kismet/GameplayStatics.h"

AMyProjectCharacter::AMyProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	Stats = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AMyProjectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyProjectCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AMyProjectCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyProjectCharacter::Look);
		
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AMyProjectCharacter::LightAttack);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AMyProjectCharacter::CastFire);
		EnhancedInputComponent->BindAction(HealAction, ETriggerEvent::Started, this, &AMyProjectCharacter::CastHeal);
		EnhancedInputComponent->BindAction(MenuAction, ETriggerEvent::Started, this, &AMyProjectCharacter::ToggleMenu);
	}

	else
	{
		UE_LOG(LogMyProject, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AMyProjectCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void AMyProjectCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AMyProjectCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AMyProjectCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AMyProjectCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void AMyProjectCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}
void AMyProjectCharacter::LightAttack()
{
		if (bMenuOpen) return;
	const FVector Center = GetActorLocation() + GetActorForwardVector() * AttackRange;

	TArray<FOverlapResult> Overlaps;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	GetWorld()->OverlapMultiByChannel(Overlaps, Center, FQuat::Identity, ECC_Pawn,
		FCollisionShape::MakeSphere(AttackRadius), Params);

	TSet<AActor*> AlreadyHit;
	for (const FOverlapResult& Result : Overlaps)
	{
		AActor* Target = Result.GetActor();
		if (!Target || AlreadyHit.Contains(Target)) continue;
		AlreadyHit.Add(Target);

		if (UStatsComponent* TargetStats = Target->FindComponentByClass<UStatsComponent>())
		{
			TargetStats->TakeDamage(Stats->Attack);
			Stats->AddATB(ATBGainPerHit);
		}
	}

	DrawDebugSphere(GetWorld(), Center, AttackRadius, 12, FColor::Red, false, 0.3f);
}
void AMyProjectCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			if (UPlayerHUDWidget* HUD = CreateWidget<UPlayerHUDWidget>(PC, HUDWidgetClass))
			{
				HUD->AddToViewport();
				HUD->BindToStats(Stats);
			}
		}
	}
}
AEnemyCharacter* AMyProjectCharacter::FindNearestEnemy(float MaxRange) const
{
	AEnemyCharacter* Best = nullptr;
	float BestDist = MaxRange;

	for (TActorIterator<AEnemyCharacter> It(GetWorld()); It; ++It)
	{
		AEnemyCharacter* Enemy = *It;
		if (Enemy->Stats->IsDead()) continue;

		const float Dist = FVector::Dist(GetActorLocation(), Enemy->GetActorLocation());
		if (Dist < BestDist)
		{
			BestDist = Dist;
			Best = Enemy;
		}
	}
	return Best;
}

void AMyProjectCharacter::CastFire()
{
	if (Stats->GetFullATBBars() < 1 || Stats->MP < FireMPCost)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Yellow, TEXT("Not enough ATB or MP"));
		return;
	}

	AEnemyCharacter* Target = FindNearestEnemy(FireRange);
	if (!Target)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Yellow, TEXT("No target in range"));
		return;
	}

	Stats->SpendATBBars(1);
	Stats->SpendMP(FireMPCost);
	Target->Stats->TakeDamage(FireDamage);

	DrawDebugLine(GetWorld(), GetActorLocation(), Target->GetActorLocation(), FColor::Orange, false, 0.5f, 0, 5.f);
}

void AMyProjectCharacter::CastHeal()
{
	if (Stats->GetFullATBBars() < 1 || Stats->MP < HealMPCost)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Yellow, TEXT("Not enough ATB or MP"));
		return;
	}

	Stats->SpendATBBars(1);
	Stats->SpendMP(HealMPCost);
	Stats->Heal(HealAmount);
}
void AMyProjectCharacter::ToggleMenu()
{
	if (bMenuOpen) CloseMenu(); else OpenMenu();
}

void AMyProjectCharacter::OpenMenu()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC || !MenuWidgetClass || Stats->IsDead()) return;

	if (!MenuWidget)
	{
		MenuWidget = CreateWidget<UCommandMenuWidget>(PC, MenuWidgetClass);
		MenuWidget->OnCommandChosen.AddDynamic(this, &AMyProjectCharacter::HandleCommandChosen);
	}

	const bool bCanFire = Stats->GetFullATBBars() >= 1 && Stats->MP >= FireMPCost;
	const bool bCanHeal = Stats->GetFullATBBars() >= 1 && Stats->MP >= HealMPCost;
	MenuWidget->Refresh(bCanFire, bCanHeal);
	MenuWidget->AddToViewport();

	bMenuOpen = true;
	UGameplayStatics::SetGlobalTimeDilation(this, MenuTimeDilation);
	PC->SetIgnoreLookInput(true);
	PC->bShowMouseCursor = true;

	FInputModeGameAndUI Mode;
	Mode.SetHideCursorDuringCapture(false);
	Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PC->SetInputMode(Mode);
}

void AMyProjectCharacter::CloseMenu()
{
	if (!bMenuOpen) return;
	bMenuOpen = false;

	if (MenuWidget) MenuWidget->RemoveFromParent();
	UGameplayStatics::SetGlobalTimeDilation(this, 1.f);

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		PC->SetIgnoreLookInput(false);
		PC->bShowMouseCursor = false;
		PC->SetInputMode(FInputModeGameOnly());
	}
}

void AMyProjectCharacter::HandleCommandChosen(int32 CommandIndex)
{
	CloseMenu();   // restore normal time first

	switch (CommandIndex)
	{
	case 0: CastFire(); break;
	case 1: CastHeal(); break;
	default: break;
	}
}