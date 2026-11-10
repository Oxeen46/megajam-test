#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StatsComponent.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class MYPROJECT_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="RPG")
	TObjectPtr<UStatsComponent> Stats;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleDeath(AActor* DeadActor);
};