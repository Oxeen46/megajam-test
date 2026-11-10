#include "CommandMenuWidget.h"

void UCommandMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	FireButton->OnClicked.AddDynamic(this, &UCommandMenuWidget::OnFireClicked);
	HealButton->OnClicked.AddDynamic(this, &UCommandMenuWidget::OnHealClicked);
}

void UCommandMenuWidget::Refresh(bool bCanFire, bool bCanHeal)
{
	FireButton->SetIsEnabled(bCanFire);
	HealButton->SetIsEnabled(bCanHeal);
}

void UCommandMenuWidget::OnFireClicked() { OnCommandChosen.Broadcast(0); }
void UCommandMenuWidget::OnHealClicked() { OnCommandChosen.Broadcast(1); }