// Fill out your copyright notice in the Description page of Project Settings.

#include "TestEnemy.h"


// Sets default values
ATestEnemy::ATestEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestEnemy::BeginPlay()
{
	Super::BeginPlay();

	isAlreadyDead = false;
	CheckForComponents();
	SetupCombatComponent();
}

// Called every frame
void ATestEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!isAlreadyDead && !TestIsAlive())
	{
		PerformDeath();
	}
}

// Detect and store components, log errors if nonexistent
void ATestEnemy::CheckForComponents()
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

// Initialize variables to desired value inside combat component
void ATestEnemy::SetupCombatComponent()
{
	CombatComponent->SetMaxHitpoints(100.0f);
	CombatComponent->SetIsDeathAllowed(true);
	CombatComponent->SetIsAlive(true);
}

// Test if the combat component is alive
bool ATestEnemy::TestIsAlive()
{
	if (CombatComponent->GetIsAlive() == false)
	{
		return false;
	}
	return true;
}

// Perform appropriate actions upon death
void ATestEnemy::PerformDeath()
{
	StaticMeshComponent->SetVisibility(false);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called to bind functionality to input
void ATestEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

