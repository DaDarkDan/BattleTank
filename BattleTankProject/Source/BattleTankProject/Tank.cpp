// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	tankAimingComp = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector hitLocation) {
	tankAimingComp->AimAt(hitLocation, launchSpeed);
}

void ATank::Fire() {
	UE_LOG(LogTemp, Warning, TEXT("Fire() called"));
}


void ATank::SetBarrel(UTankBarrel* barrel) {
	tankAimingComp->SetBarrel(barrel);
}

void ATank::SetTurret(UTankTurret* turret) {
	tankAimingComp->SetTurret(turret);
}