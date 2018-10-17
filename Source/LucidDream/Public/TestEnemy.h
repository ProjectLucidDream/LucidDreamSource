// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CombatComponent.h"
#include "TestEnemy.generated.h"

UCLASS()
class LUCIDDREAM_API ATestEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Detect and store components, log errors if nonexistent
	void CheckForComponents();

	// Initialize variables to desired value inside combat component
	void SetupCombatComponent();

	// Test if the combat component is alive
	bool TestIsAlive();

	// Perform appropriate actions upon death
	void PerformDeath();

private:
	// Combat component stored here
	UCombatComponent* CombatComponent = nullptr;

	// Capsule component stored here
	UCapsuleComponent* CapsuleComponent = nullptr;

	// Static mesh component stored here
	UStaticMeshComponent* StaticMeshComponent = nullptr;

	// Remember if dead to reduce processor load
	bool isAlreadyDead;

};
