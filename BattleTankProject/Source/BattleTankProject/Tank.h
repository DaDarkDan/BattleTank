// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANKPROJECT_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector hitLocation);

	//TODO remove once firing is moved to aiming component
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float launchSpeed = 4000;

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

protected:	
	UPROPERTY(BluePrintReadOnly)
		UTankAimingComponent* tankAimingComp = nullptr;

	virtual void BeginPlay() override;

private:	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> projectileBP;

	UTankBarrel* barrel = nullptr; //TODO remove

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float reloadTimeInSeconds = 3;

	double lastFiringTime = 0;
};
