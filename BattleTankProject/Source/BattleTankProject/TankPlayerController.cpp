// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();	

	auto aimingComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if(!ensure(aimingComp)) { return; }
	FoundAimingComponent(aimingComp);

}

void ATankPlayerController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {
	auto aimingComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if(!ensure(aimingComp)) { return; }

	FVector hitLocation;
	if(GetSightRayHitLocation(hitLocation)) {
		aimingComp->AimAt(hitLocation);
	}
}

//Get world location of linetrace through crosshair, true if it hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& outHitLocation) const {

	//find crosshair position
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);
	FVector2D screenLocation = FVector2D(viewportSizeX*crosshairXLocation, viewportSizeY*crosshairYLocation);

	//de-project screen position of crosshair to world direction
	FVector lookDirection;
	if(GetLookDirection(screenLocation, lookDirection)) {
		//line trace along that lookDirection
		GetLookVectorHitLocation(lookDirection, outHitLocation);
	}	
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector& worldDirection) const {
	FVector cameraWorldLocation; //to be discarded
	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraWorldLocation, worldDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection, FVector& outHitLocation) const {
	FHitResult hitResult;
	auto startLocation = PlayerCameraManager->GetCameraLocation();
	if(GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, startLocation + lookDirection*lineTraceRange, ECollisionChannel::ECC_Visibility)) {
		outHitLocation = hitResult.Location;
		return true;
	}
	outHitLocation = FVector(0);
	return false;
}