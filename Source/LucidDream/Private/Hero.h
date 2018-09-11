// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "CombatComponent.h"
#include "DrawDebugHelpers.h"
#include "Hero.generated.h"

UCLASS()
class AHero : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHero();

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

	// Set max jumps based on whether double jumping is enabled
	void SetDoubleJumpEnabled(bool isEnabled);
	void SetDoubleJumpEnabled();

	// Move player forward
	void MoveForward(float Value);
	// Move player right
	void MoveRight(float Value);
	// Turn on the azimuth axis
	void FacingAzimuth(float Value);
	// Turn on pitch axis
	void FacingPitch(float Value);

	// Perform a basic attack
	void AttackBasic();

	// Raycast for knife attack
	FHitResult RaycastKnife();

	// Sprint event
	UFUNCTION(BlueprintImplementableEvent)
		void HandleSprint();

private:
	// Determines whether sprinting is unlocked
	bool sprintEnabled;

	// Determines whether double jumping is unlocked
	bool doubleJumpEnabled;

	// Movement component stored here
	UCharacterMovementComponent* MovementComponent = nullptr;

	// Spring arm component stored here
	USpringArmComponent* SpringArmComponent = nullptr;

	// Combat component stored here
	UCombatComponent* CombatComponent = nullptr;
};
