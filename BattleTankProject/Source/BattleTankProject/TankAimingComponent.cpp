// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed) {
	if(!barrel) { return; }

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
		auto aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(aimDirection);
		MoveTurretTowards(aimDirection);
		//UE_LOG(LogTemp, Warning, TEXT("%f: aim solution found at %s"), GetWorld()->GetTimeSeconds(), *aimDirection.ToString());
	} else {
		//UE_LOG(LogTemp, Warning, TEXT("%f: no aim solution found"), GetWorld()->GetTimeSeconds());
	}

}


void UTankAimingComponent::SetBarrel(UTankBarrel* barrel) {
	if(!barrel) { return; }
	this->barrel = barrel;
}

void UTankAimingComponent::SetTurret(UTankTurret* turret) {
	if(!turret) { return; }
	this->turret = turret;
}


void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection) {
	barrel->Elevate(CalculateRotationDelta(aimDirection, turret->GetForwardVector().Rotation()).Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector aimDirection) {
	turret->Rotate(CalculateRotationDelta(aimDirection, turret->GetForwardVector().Rotation()).Yaw);
}

FRotator UTankAimingComponent::CalculateRotationDelta(FVector aimDirection, FRotator meshRotation) {
	return aimDirection.Rotation() - meshRotation;
}