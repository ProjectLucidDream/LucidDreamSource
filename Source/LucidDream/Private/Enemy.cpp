// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	isAlreadyDead = false;
	CheckForComponents();
	SetupCombatComponent();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!isAlreadyDead && !TestIsAlive())
	{
		PerformDeath();
	}
}

// Detect and store components, log errors if nonexistent
void AEnemy::CheckForComponents()
{
	CombatComponent = this->FindComponentByClass<UCombatComponent>();

	if (CombatComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No combat component connected to %s"), *this->GetName());
	}

	CapsuleComponent = this->FindComponentByClass<UCapsuleComponent>();

	if (CapsuleComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No capsule component connected to %s"), *this->GetName());
	}

	StaticMeshComponent = this->FindComponentByClass<UStaticMeshComponent>();

	if (StaticMeshComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No static mesh component connected to %s"), *this->GetName());
	}
}

// Initialize variables to desired values inside combat component
void AEnemy::SetupCombatComponent()
{
	if (CombatComponent != nullptr)
	{
		CombatComponent->SetMaxHitpoints(100.0f);
		CombatComponent->SetIsDeathAllowed(true);
		CombatComponent->SetIsAlive(true);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Combat component setup failed for %s"), *this->GetName());
	}
}

// Test if the combat component is alive
bool AEnemy::TestIsAlive()
{
	if (CombatComponent->GetIsAlive() == false)
	{
		return false;
	}
	return true;
}

// Perform appropriate actions upon death
void AEnemy::PerformDeath()
{
	StaticMeshComponent->SetVisibility(false);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

