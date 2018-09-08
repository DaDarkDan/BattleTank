// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANKPROJECT_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:

	ATank* GetControlledTank() const;

	
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& outHitLocation) const;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
		float crosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
		float crosshairYLocation = 0.3333f;

	UPROPERTY(EditAnywhere)
		float lineTraceRange = 1000000.0f; //10km

	bool GetLookDirection(FVector2D screenLocation, FVector& worldDirection) const;
	
	bool GetLookVectorHitLocation(FVector lookDirection, FVector& hitLocation) const;
};
