// Fill out your copyright notice in the Description page of Project Settings.

#include "Hero.h"


// Sets default values
AHero::AHero()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHero::BeginPlay()
{
	Super::BeginPlay();

	// Initialize ability unlocks
		// TODO read default from memory
	sprintEnabled = true;
	doubleJumpEnabled = false;

	MovementComponent = this->GetCharacterMovement();

	SetDoubleJumpEnabled();
}

// Called every frame
void AHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (sprintEnabled)
	{
		HandleSprint();
	}
}

// Called to bind functionality to input
void AHero::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	// set up gameplay key bindings
	check(InputComponent);
	InputComponent->BindAxis("MoveForward", this, &AHero::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AHero::MoveRight);
	InputComponent->BindAxis("FacingAzimuth", this, &AHero::FacingAzimuth);
}

// Set max jumps based on whether double jumping is enabled
void AHero::SetDoubleJumpEnabled(bool isEnabled)
{
	doubleJumpEnabled = isEnabled == NULL ? false : isEnabled;
	if (doubleJumpEnabled)
	{
		this->JumpMaxCount = 2;
	}
	else
	{
		this->JumpMaxCount = 1;
	}
}

void AHero::SetDoubleJumpEnabled()
{
	if (doubleJumpEnabled)
	{
		this->JumpMaxCount = 2;
	}
	else
	{
		this->JumpMaxCount = 1;
	}
}

void AHero::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		// Limit pitch when walking or falling
		if (MovementComponent->IsMovingOnGround() || MovementComponent->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}
		// add movement in that direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AHero::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		// Limit pitch when walking or falling
		if (MovementComponent->IsMovingOnGround() || MovementComponent->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}
		// add movement in that direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AHero::FacingAzimuth(float Value)
{
	this->AddControllerYawInput(Value);
}