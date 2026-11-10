#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnStatChanged, float, NewValue, float, MaxValue, float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDied, AActor*, DeadActor);

UCLASS(ClassGroup=(RPG), meta=(BlueprintSpawnableComponent))
class MYPROJECT_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UStatsComponent();

	// ---- Health ----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats|Health")
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stats|Health")
	float Health;

	// ---- Magic ----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats|Magic")
	float MaxMP = 50.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stats|Magic")
	float MP;

	// ---- Combat stats ----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats|Combat")
	float Attack = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats|Combat")
	float Defense = 5.f;

	// ---- ATB: each bar = 100, so 200 max = 2 bars like FF7R ----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats|ATB")
	int32 MaxATBBars = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats|ATB")
	float ATBFillPerSecond = 5.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stats|ATB")
	float ATB = 0.f;

	// ---- Events (bind these in Blueprint/UI) ----
	UPROPERTY(BlueprintAssignable) FOnStatChanged OnHealthChanged;
	UPROPERTY(BlueprintAssignable) FOnStatChanged OnMPChanged;
	UPROPERTY(BlueprintAssignable) FOnStatChanged OnATBChanged;
	UPROPERTY(BlueprintAssignable) FOnDied OnDied;

	// ---- Functions ----
	UFUNCTION(BlueprintCallable, Category="Stats") void TakeDamage(float RawDamage);
	UFUNCTION(BlueprintCallable, Category="Stats") void Heal(float Amount);
	UFUNCTION(BlueprintCallable, Category="Stats") bool SpendMP(float Amount);
	UFUNCTION(BlueprintCallable, Category="Stats") void AddATB(float Amount);
	UFUNCTION(BlueprintCallable, Category="Stats") bool SpendATBBars(int32 Bars);
	UFUNCTION(BlueprintPure, Category="Stats") int32 GetFullATBBars() const;
	UFUNCTION(BlueprintPure, Category="Stats") bool IsDead() const { return Health <= 0.f; }

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};