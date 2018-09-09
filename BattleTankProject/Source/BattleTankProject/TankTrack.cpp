// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float throttle) {
	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *GetName(), throttle);

	FVector forceApplied = GetForwardVector() * throttle * trackMaxDrivingForce;
	UPrimitiveComponent* tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); //add force at highest possible class

	tankRoot->AddForceAtLocation(forceApplied, GetComponentLocation());
}

