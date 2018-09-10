// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Engine/World.h"


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

	bool isReloaded = (FPlatformTime::Seconds() - lastFiringTime) > reloadTimeInSeconds;
	if(barrel && isReloaded) { 
		//spawn projectile at socket of barrel
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(projectileBP, barrel->GetSocketLocation(FName("ProjectileLaunchSocket")), barrel->GetSocketRotation(FName("ProjectileLaunchSocket")));
		projectile->LaunchProjectile(launchSpeed);
		lastFiringTime = FPlatformTime::Seconds();
	}

}


void ATank::SetBarrel(UTankBarrel* barrel) {
	tankAimingComp->SetBarrel(barrel);
	this->barrel = barrel;
}

void ATank::SetTurret(UTankTurret* turret) {
	tankAimingComp->SetTurret(turret);
}