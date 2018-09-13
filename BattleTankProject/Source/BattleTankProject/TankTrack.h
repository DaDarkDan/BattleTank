// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force and to apply forces to the tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKPROJECT_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float throttle);
	
	//max force per track in Newtons (force = mass * acceleration)
	UPROPERTY(EditDefaultsOnly)
		float trackMaxDrivingForce = 80000000; //old: 100000000
};
