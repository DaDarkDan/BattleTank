// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* leftTrack, UTankTrack* rightTrack) {
	this->leftTrack = leftTrack;
	this->rightTrack = rightTrack;
	UE_LOG(LogTemp, Warning, TEXT("Tankmovementcomp for %s initialized"), *GetOwner()->GetName());

}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	FVector tankForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector aiForwardIntention = MoveVelocity.GetSafeNormal();
	
	float forwardThrow = FVector::DotProduct(tankForwardVector, aiForwardIntention);
	IntendMoveForward(forwardThrow);

	float rightThrow = FVector::CrossProduct(aiForwardIntention, tankForwardVector).Z;
	IntendTurnRight(rightThrow);
	
	UE_LOG(LogTemp, Warning, TEXT("%f"), rightThrow);
}


void UTankMovementComponent::IntendMoveForward(float controlThrow) {
	if(!leftTrack || !rightTrack) { return; }

	leftTrack->SetThrottle(controlThrow);
	rightTrack->SetThrottle(controlThrow);

	//TODO preventdouble speed due to dual control
}

void UTankMovementComponent::IntendTurnRight(float controlThrow) {
	if(!leftTrack || !rightTrack) { return; }

	float sidewardFactor = 3; //TODO adjust (not in the course)
	leftTrack->SetThrottle(sidewardFactor*controlThrow);
	rightTrack->SetThrottle(sidewardFactor *-controlThrow);

	//TODO preventdouble speed due to dual control
}
