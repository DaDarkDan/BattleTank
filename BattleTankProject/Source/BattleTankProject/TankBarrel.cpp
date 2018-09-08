// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float relativeSpeed) {
	//clamp relativeSpeed between -1 and +1
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1.f, 1.f);

	float elevationChange = relativeSpeed * maxElevationDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float rawNewElevation = RelativeRotation.Pitch + elevationChange;
	float elevation = FMath::Clamp<float>(rawNewElevation, minElevationDegrees, maxElevationDegrees);
	
	SetRelativeRotation(FRotator(elevation, 0, 0));
}


