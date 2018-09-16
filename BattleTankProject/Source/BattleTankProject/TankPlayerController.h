// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "TankPlayerController.generated.h"

class ATank;

/*
* Responsible for helping the player aim
*/
UCLASS()
class BATTLETANKPROJECT_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BluePrintCallable, Category = "Setup")
		ATank* GetControlledTank() const;

	UFUNCTION(BluePrintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);
private:
	
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& outHitLocation) const;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly)
		float crosshairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
		float crosshairYLocation = 0.3333f;

	UPROPERTY(EditDefaultsOnly)
		float lineTraceRange = 1000000.0f; //10km

	bool GetLookDirection(FVector2D screenLocation, FVector& worldDirection) const;
	
	bool GetLookVectorHitLocation(FVector lookDirection, FVector& hitLocation) const;
};
