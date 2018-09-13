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
	UFUNCTION(BluePrintCallable, Category = "Setup")
		void Initialize(UTankTrack* leftTrack, UTankTrack* rightTrack);

	UFUNCTION(BluePrintCallable, Category = "Input")
		void IntendMoveForward(float controlThrow);	

	UFUNCTION(BluePrintCallable, Category = "Input")
		void IntendTurnRight(float controlThrow);

private:
	//gets input from pathfinding logic which gets input from MoveToActor() in AIcontroller
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack * leftTrack = nullptr;
	UTankTrack * rightTrack = nullptr;
};
