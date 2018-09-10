// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;

UCLASS()
class BATTLETANKPROJECT_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector hitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrel(UTankBarrel* barrel);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurret(UTankTurret* turret);

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float launchSpeed = 4000;

	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();

protected:
	UTankAimingComponent* tankAimingComp = nullptr;

	UPROPERTY(BluePrintReadOnly)
		UTankMovementComponent* tankMovementComp = nullptr;

private:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; 

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;	

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> projectileBP; //alternative: Tsubclassof

	UTankBarrel* barrel = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float reloadTimeInSeconds = 3;

	double lastFiringTime = 0;
};
