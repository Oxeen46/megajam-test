// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

class AEnemyCharacter;
#include  "PlayerHUDWidget.h"
#include "StatsComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "MyProjectCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UCommandMenuWidget;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class AMyProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> AttackAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI")
	TSubclassOf<UPlayerHUDWidget> HUDWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	float AttackRange = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	float AttackRadius = 90.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	float ATBGainPerHit = 8.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> HealAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Abilities")
	float FireDamage = 40.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Abilities")
	float FireMPCost = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Abilities")
	float FireRange = 1500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Abilities")
	float HealAmount = 40.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Abilities")
	float HealMPCost = 4.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
    TObjectPtr<UInputAction> MenuAction;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI")
    TSubclassOf<UCommandMenuWidget> MenuWidgetClass;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
    float MenuTimeDilation = 0.1f;
    
    UPROPERTY()
    TObjectPtr<UCommandMenuWidget> MenuWidget;
    
    bool bMenuOpen = false;
    
    void ToggleMenu();
    void OpenMenu();
    void CloseMenu();
    
    UFUNCTION()
    void HandleCommandChosen(int32 CommandIndex);

	void CastFire();
	void CastHeal();
	AEnemyCharacter* FindNearestEnemy(float MaxRange) const;

	void LightAttack();

public:

	/** Constructor */
	AMyProjectCharacter();	

protected:

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

public:

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="RPG")
	TObjectPtr<UStatsComponent> Stats;

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

