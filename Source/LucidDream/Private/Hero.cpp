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

	CheckForComponents();
	SetupCombatComponent();

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
	InputComponent->BindAxis("FacingPitch", this, &AHero::FacingPitch);
	InputComponent->BindAction("AttackBasic", EInputEvent::IE_Pressed, this, &AHero::AttackBasic);
}

// Detect and store components, log errors if nonexistent
void AHero::CheckForComponents()
{
	SpringArmComponent = this->FindComponentByClass<USpringArmComponent>();
	MovementComponent = this->GetCharacterMovement();
	CombatComponent = this->FindComponentByClass<UCombatComponent>();

	if (SpringArmComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No spring arm component connected to %s"), *this->GetName());
	}
	if (MovementComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No movement component connected to %s"), *this->GetName());
	}
	if (CombatComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No combat component connected to %s"), *this->GetName());
	}
}

// Initialize variables to desired value inside combat component
void AHero::SetupCombatComponent()
{
	CombatComponent->SetMaxHitpoints(100.0f);
	CombatComponent->SetIsDeathAllowed(true);
	CombatComponent->SetIsAlive(true);
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

// Set max jumps based on whether double jumping is enabled
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

// Raycast for knife attack
FHitResult AHero::RaycastKnife()
{
	FHitResult FirstActorHit;
	float CapsuleRadius = GetCapsuleComponent()->GetScaledCapsuleRadius() + 5.0f;
	FVector ForwardVector = GetActorForwardVector();
	FVector TraceStart = GetActorLocation() + (ForwardVector * CapsuleRadius);

	FVector TraceEnd = ((ForwardVector * 65.0f) + TraceStart);
	FCollisionQueryParams CollisionParams;

	this->GetWorld()->LineTraceSingleByChannel(FirstActorHit, TraceStart, TraceEnd, ECollisionChannel::ECC_Pawn, CollisionParams);

	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor(0.0f, 0.0f, 0.0f), true);

	return FirstActorHit;
}

// Move player forward
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

// Move player right
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

// Turn on the yaw axis
void AHero::FacingAzimuth(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		this->AddControllerYawInput(Value);
	}
}

// Turn on the pitch axis
void AHero::FacingPitch(float Value)
{
	if ((Controller != NULL) 
		&& (Value != 0.0f) 
		&& (SpringArmComponent->GetComponentRotation().Pitch + Value <= 89)
		&& (SpringArmComponent->GetComponentRotation().Pitch + Value >= -89))
	{ 
		FRotator *DeltaRotation = new FRotator(Value, 0.0f, 0.0f);
		SpringArmComponent->AddLocalRotation(*DeltaRotation);
	}
}

// Perform a basic attack
void AHero::AttackBasic()
{
	auto ComponentHit = RaycastKnife().GetComponent();
		if (ComponentHit == nullptr) { return; }
	AActor* ActorHit = ComponentHit->GetOwner();
		if (ActorHit == nullptr) { return; }
	UCombatComponent* Target = ActorHit->FindComponentByClass<UCombatComponent>();
		if (Target == nullptr) { return; }

	if (Target->GetIsAlive() == true)
	{
		CombatComponent->DealDamage(45, Target);

		// Perform an operation if this blow killed the opponent
		if (Target->GetIsAlive() == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("Dead!"));
		}
	}
	else
	// Perform if this blow failed due to target already being dead
	{
		UE_LOG(LogTemp, Warning, TEXT("Omae, wa mou shindeiru!"));
	}
}