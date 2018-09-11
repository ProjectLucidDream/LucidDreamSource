// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUCIDDREAM_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Getters
	bool GetIsAlive();

	// Setters
	void SetMaxHitpoints(float value);
	void SetIsDeathAllowed(bool value);
	void SetIsAlive(bool value);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Give default values to uninitialized variables and constants
	void CheckVariables();

	// Deal damage to another character via their combat component
	void DealDamage(float amount, UCombatComponent* target);

	// Take a given amount of damage
	void TakeDamage(float amount);

	// Heal target for set amount
	void HealTarget(float amount, UCombatComponent* target);

	// Heal self for set amount
	void HealSelf(float amount);

	// Handle death if enabled
	void Killed();

private:
	// The hitpoints of the owning actor
	float MaxHitpoints = NULL;
	float Hitpoints;
	
	// Whether character is allowed to die
	bool IsDeathAllowed = NULL;

	// Whether character is alive
	bool IsAlive = NULL;
};
