// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/*
* Responsible from driving the tank tracks
*/
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKPROJECT_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BluePrintCallable, Category = Setup)
		void Initialize(UTankTrack* leftTrack, UTankTrack* rightTrack);

	UFUNCTION(BluePrintCallable, Category = Input)
		void intendMoveForward(float controlThrow);	

	UFUNCTION(BluePrintCallable, Category = Input)
		void intendTurnRight(float controlThrow);

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:
	UTankTrack * leftTrack = nullptr;
	UTankTrack * rightTrack = nullptr;
};
