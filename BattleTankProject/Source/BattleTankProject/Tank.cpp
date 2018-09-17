// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay() {
	Super::BeginPlay(); //NEEDED TO CALL BEGINPLAY IN BLUEPRINT!!!

	tankAimingComp = FindComponentByClass<UTankAimingComponent>();
}


void ATank::AimAt(FVector hitLocation) {
	if(!ensure(tankAimingComp)) { return; }

	tankAimingComp->AimAt(hitLocation, launchSpeed);
}

void ATank::Fire() {

	bool isReloaded = (FPlatformTime::Seconds() - lastFiringTime) > reloadTimeInSeconds;
	if(ensure(barrel && isReloaded)) { 
		//spawn projectile at socket of barrel
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(projectileBP, barrel->GetSocketLocation(FName("ProjectileLaunchSocket")), barrel->GetSocketRotation(FName("ProjectileLaunchSocket")));
		projectile->LaunchProjectile(launchSpeed);
		lastFiringTime = FPlatformTime::Seconds();
	}

}