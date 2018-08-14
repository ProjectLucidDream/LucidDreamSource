// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatComponent.h"


// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	Hitpoints = INITIAL_HITPOINTS;
	
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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
	if (Hitpoints < 0)
	{
		Hitpoints = 0;
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
	if (Hitpoints > INITIAL_HITPOINTS)
	{
		Hitpoints = INITIAL_HITPOINTS;
	}
}