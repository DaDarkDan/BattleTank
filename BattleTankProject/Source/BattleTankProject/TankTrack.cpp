// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float throttle) {
	FVector forceApplied = GetForwardVector() * throttle * trackMaxDrivingForce;
	FRotator alteredAngle = FRotator(0, 0, 0);

	UPrimitiveComponent* tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); //add force at highest possible class

	tankRoot->AddForceAtLocation(forceApplied, GetComponentLocation());
}

