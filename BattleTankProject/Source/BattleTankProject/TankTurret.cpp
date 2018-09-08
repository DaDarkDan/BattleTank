// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float relativeSpeed) {
	//clamp relativeSpeed between -1 and +1
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1.f, 1.f);

	float rotationSpeed = relativeSpeed * maxRotationDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float rotation = rotationSpeed + RelativeRotation.Yaw;

	SetRelativeRotation(FRotator(0, rotation, 0));
}