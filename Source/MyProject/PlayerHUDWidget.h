#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "PlayerHUDWidget.generated.h"

class UStatsComponent;

UCLASS()
class MYPROJECT_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindToStats(UStatsComponent* Stats);

protected:
	UPROPERTY(meta=(BindWidget)) TObjectPtr<UProgressBar> HealthBar;
	UPROPERTY(meta=(BindWidget)) TObjectPtr<UProgressBar> MPBar;
	UPROPERTY(meta=(BindWidget)) TObjectPtr<UProgressBar> ATBBar1;
	UPROPERTY(meta=(BindWidget)) TObjectPtr<UProgressBar> ATBBar2;

	UFUNCTION() void HandleHealth(float NewValue, float MaxValue, float Delta);
	UFUNCTION() void HandleMP(float NewValue, float MaxValue, float Delta);
	UFUNCTION() void HandleATB(float NewValue, float MaxValue, float Delta);
};