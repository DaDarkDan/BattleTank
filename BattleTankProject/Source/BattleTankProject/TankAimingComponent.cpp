// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay() {
	Super::BeginPlay();
	//wait one reload time
	lastFiringTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	if((FPlatformTime::Seconds() - lastFiringTime) < reloadTimeInSeconds) {
		firingState = EFiringState::Reloading;
		UE_LOG(LogTemp, Warning, TEXT("reloading"));
	} else if (IsBarrelMoving()) {
		firingState = EFiringState::Aiming;
		UE_LOG(LogTemp, Warning, TEXT("aiming"));
	} else {
		firingState = EFiringState::Locked;
		UE_LOG(LogTemp, Warning, TEXT("locked"));
	}
}

bool UTankAimingComponent::IsBarrelMoving() const {
	if(!ensure(barrel)) { return false; }

	return !aimDirection.Equals(barrel->GetForwardVector().GetSafeNormal(), 0.1f); //equal = not moving
}



void UTankAimingComponent::Initialize(UTankBarrel* barrel, UTankTurret* turret) {
	this->barrel = barrel;
	this->turret = turret;
	UE_LOG(LogTemp, Warning, TEXT("Tank aiming comp for %s initialized"), *GetOwner()->GetName());
}

void UTankAimingComponent::AimAt(FVector hitLocation) {
	if(!ensure(barrel && turret)) { return; }

	FVector outLaunchVelocity;
	FVector startLocation = barrel->GetSocketLocation(FName("ProjectileLaunchSocket"));
	//Calculate the outLaunchVelocity
	if(UGameplayStatics::SuggestProjectileVelocity(
		this,
		outLaunchVelocity,
		startLocation,
		hitLocation,
		launchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*>(),
		true
		)) {
		aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(aimDirection);
		MoveTurretTowards(aimDirection);
	} 

}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection) {
	if(!ensure(barrel && turret)) { return; }

	barrel->Elevate(CalculateRotationDelta(aimDirection, turret->GetForwardVector().Rotation()).Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector aimDirection) {
	if(!ensure(turret)) { return; }

	turret->Rotate(CalculateRotationDelta(aimDirection, turret->GetForwardVector().Rotation()).Yaw);
}

FRotator UTankAimingComponent::CalculateRotationDelta(FVector aimDirection, FRotator meshRotation) {
	return aimDirection.Rotation() - meshRotation;
}

void UTankAimingComponent::Fire() {

	if(firingState != EFiringState::Reloading) {
		if(!ensure(barrel && projectileBP)) { return; }
		//spawn projectile at socket of barrel
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(projectileBP, barrel->GetSocketLocation(FName("ProjectileLaunchSocket")), barrel->GetSocketRotation(FName("ProjectileLaunchSocket")));
		projectile->LaunchProjectile(launchSpeed);
		lastFiringTime = FPlatformTime::Seconds();
	}

}