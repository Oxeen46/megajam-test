#include "StatsComponent.h"

UStatsComponent::UStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	MP = MaxMP;
}

void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!IsDead())
	{
		AddATB(ATBFillPerSecond * DeltaTime);
	}
}

void UStatsComponent::TakeDamage(float RawDamage)
{
	if (IsDead()) return;

	const float Final = FMath::Max(1.f, RawDamage - Defense);
	const float Old = Health;
	Health = FMath::Clamp(Health - Final, 0.f, MaxHealth);
	OnHealthChanged.Broadcast(Health, MaxHealth, Health - Old);

	if (Health <= 0.f)
	{
		OnDied.Broadcast(GetOwner());
	}
}

void UStatsComponent::Heal(float Amount)
{
	if (IsDead()) return;
	const float Old = Health;
	Health = FMath::Clamp(Health + Amount, 0.f, MaxHealth);
	OnHealthChanged.Broadcast(Health, MaxHealth, Health - Old);
}

bool UStatsComponent::SpendMP(float Amount)
{
	if (MP < Amount) return false;
	MP -= Amount;
	OnMPChanged.Broadcast(MP, MaxMP, -Amount);
	return true;
}

void UStatsComponent::AddATB(float Amount)
{
	const float Max = MaxATBBars * 100.f;
	const float Old = ATB;
	ATB = FMath::Clamp(ATB + Amount, 0.f, Max);
	if (!FMath::IsNearlyEqual(Old, ATB))
	{
		OnATBChanged.Broadcast(ATB, Max, ATB - Old);
	}
}

int32 UStatsComponent::GetFullATBBars() const
{
	return FMath::FloorToInt(ATB / 100.f);
}

bool UStatsComponent::SpendATBBars(int32 Bars)
{
	if (GetFullATBBars() < Bars) return false;
	AddATB(-Bars * 100.f);
	return true;
}