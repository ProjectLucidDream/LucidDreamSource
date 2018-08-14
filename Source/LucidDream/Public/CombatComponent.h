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
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Deal damage to another character via their combat component
	void DealDamage(float amount, UCombatComponent* target);

	// Take a given amount of damage
	void TakeDamage(float amount);

	// Heal target for set amount
	void HealTarget(float amount, UCombatComponent* target);

	// Heal self for set amount
	void HealSelf(float amount);

private:
	// The hitpoints of the owning actor
	const float INITIAL_HITPOINTS = 100.0f;
	float Hitpoints;
	
};
