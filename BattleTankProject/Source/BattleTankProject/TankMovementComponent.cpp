// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* leftTrack, UTankTrack* rightTrack) {
	this->leftTrack = leftTrack;
	this->rightTrack = rightTrack;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	FVector tankForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector aiForwardIntention = MoveVelocity.GetSafeNormal();
	
	float forwardThrow = FVector::DotProduct(tankForwardVector, aiForwardIntention);
	
	intendMoveForward(forwardThrow);
	UE_LOG(LogTemp, Warning, TEXT("%f"), forwardThrow);
}


void UTankMovementComponent::intendMoveForward(float controlThrow) {
	if(!leftTrack || !rightTrack) { return; }

	leftTrack->SetThrottle(controlThrow);
	rightTrack->SetThrottle(controlThrow);

	//TODO preventdouble speed due to dual control
}

void UTankMovementComponent::intendTurnRight(float controlThrow) {
	if(!leftTrack || !rightTrack) { return; }

	leftTrack->SetThrottle(controlThrow);
	rightTrack->SetThrottle(-controlThrow);

	//TODO preventdouble speed due to dual control
}
