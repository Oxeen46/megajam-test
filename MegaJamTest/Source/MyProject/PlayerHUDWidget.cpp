#include "PlayerHUDWidget.h"
#include "StatsComponent.h"

void UPlayerHUDWidget::BindToStats(UStatsComponent* Stats)
{
	if (!Stats) return;

	Stats->OnHealthChanged.AddDynamic(this, &UPlayerHUDWidget::HandleHealth);
	Stats->OnMPChanged.AddDynamic(this, &UPlayerHUDWidget::HandleMP);
	Stats->OnATBChanged.AddDynamic(this, &UPlayerHUDWidget::HandleATB);

	// Show starting values
	HandleHealth(Stats->Health, Stats->MaxHealth, 0.f);
	HandleMP(Stats->MP, Stats->MaxMP, 0.f);
	HandleATB(Stats->ATB, Stats->MaxATBBars * 100.f, 0.f);
}

void UPlayerHUDWidget::HandleHealth(float NewValue, float MaxValue, float Delta)
{
	if (HealthBar) HealthBar->SetPercent(MaxValue > 0.f ? NewValue / MaxValue : 0.f);
}

void UPlayerHUDWidget::HandleMP(float NewValue, float MaxValue, float Delta)
{
	if (MPBar) MPBar->SetPercent(MaxValue > 0.f ? NewValue / MaxValue : 0.f);
}

void UPlayerHUDWidget::HandleATB(float NewValue, float MaxValue, float Delta)
{
	// Each bar is worth 100
	if (ATBBar1) ATBBar1->SetPercent(FMath::Clamp(NewValue / 100.f, 0.f, 1.f));
	if (ATBBar2) ATBBar2->SetPercent(FMath::Clamp((NewValue - 100.f) / 100.f, 0.f, 1.f));
}