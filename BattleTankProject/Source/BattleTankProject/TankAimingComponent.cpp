// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed) {
	if(!barrel) { return; }

	FVector outLaunchVelocity;
	FVector startLocation = barrel->GetSocketLocation(FName("ProjectileLaunchSocket"));
	FCollisionResponseParams collisionResponseParams;
	//Calculate the outLaunchVelocity
	if(UGameplayStatics::SuggestProjectileVelocity(
		this,
		outLaunchVelocity,
		startLocation,
		hitLocation,
		launchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		collisionResponseParams,
		TArray<AActor*>(),
		true
		)) {
		auto aimDirection = outLaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *GetOwner()->GetName(), *aimDirection.ToString());
		MoveBarrelTowards(aimDirection);
	};

}


void UTankAimingComponent::SetBarrel(UStaticMeshComponent* barrel) {
	this->barrel = barrel;
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection) {
	FRotator aimRotation;
	//calculate difference between barrel rotation and aimDirection
	FRotator barrelRotation = barrel->GetForwardVector().Rotation();
	FRotator aimAtRotation = aimDirection.Rotation();
	FRotator deltaRotation = aimAtRotation - barrelRotation;
	UE_LOG(LogTemp, Warning, TEXT("%s"), *aimAtRotator.ToString());

	//move the barrel a bit per frame

}
