// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//enum for aiming state
UENUM()
enum class EFiringState : uint8 {
	Locked,
	Aiming,
	Reloading
};

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKPROJECT_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector hitLocation, float launchSpeed);

	UFUNCTION(BluePrintCallable, Category = "Setup")
		void Initialize(UTankBarrel* barrel, UTankTurret* turret);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState firingState = EFiringState::Locked; //in protected because BP is subclass
private:
	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;

	void MoveBarrelTowards(FVector aimDirection);
	void MoveTurretTowards(FVector aimDirection);

	//calculate difference between aiming and mesh
	FRotator CalculateRotationDelta(FVector aimDirection, FRotator meshRotation);
};
