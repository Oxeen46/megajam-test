#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "CommandMenuWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCommandChosen, int32, CommandIndex);

UCLASS()
class MYPROJECT_API UCommandMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnCommandChosen OnCommandChosen;

	// Greys out commands you can't afford
	void Refresh(bool bCanFire, bool bCanHeal);

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta=(BindWidget)) TObjectPtr<UButton> FireButton;
	UPROPERTY(meta=(BindWidget)) TObjectPtr<UButton> HealButton;

	UFUNCTION() void OnFireClicked();
	UFUNCTION() void OnHealClicked();
};