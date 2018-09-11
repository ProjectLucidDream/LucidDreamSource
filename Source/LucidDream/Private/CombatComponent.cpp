// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatComponent.h"


// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

#pragma region Getters & Setters
// Getters
bool UCombatComponent::GetIsAlive() { return IsAlive; }

// Setters
void UCombatComponent::SetMaxHitpoints(float value) { MaxHitpoints = value; }
void UCombatComponent::SetIsDeathAllowed(bool value) { IsDeathAllowed = value; }
void UCombatComponent::SetIsAlive(bool value) { IsAlive = value; }

#pragma endregion

// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	CheckVariables();
	Hitpoints = MaxHitpoints;
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Give default values to uninitialized variables and constants
void UCombatComponent::CheckVariables()
{
	MaxHitpoints = MaxHitpoints == NULL ? 100.0f : MaxHitpoints;
	IsAlive = IsAlive == NULL ? true : IsAlive;
	IsDeathAllowed = IsDeathAllowed == NULL ? true : IsDeathAllowed;
}

// Cause damage to another actor via their combat component
void UCombatComponent::DealDamage(float amount, UCombatComponent* target)
{
	if (target == nullptr) 
	{ 
		UE_LOG(LogTemp, Warning, TEXT("DealDamage failed, target combat component was null pointer."));
		return; 
	}
	target->TakeDamage(amount);
}

// Take a set amount of damage
void UCombatComponent::TakeDamage(float amount)
{
	Hitpoints -= amount;
	if (Hitpoints <= 0)
	{
		Hitpoints = 0;
		Killed();
	}
}

// Heal target for set amount
void UCombatComponent::HealTarget(float amount, UCombatComponent* target)
{
	if (target == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("HealTarget failed, target combat component was null pointer."));
		return;
	}
	target->HealSelf(amount);
}

// Heal self for set amount
void UCombatComponent::HealSelf(float amount)
{
	Hitpoints += amount;
	if (Hitpoints > MaxHitpoints)
	{
		Hitpoints = MaxHitpoints;
	}
}

// Handle actor death if allowed
void UCombatComponent::Killed()
{
	if (!IsDeathAllowed)
	{
		return;
	}
	IsAlive = false;
}