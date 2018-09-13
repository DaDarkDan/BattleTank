// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	ATank* controlledTank = Cast<ATank>(GetPawn());
	ATank* playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if(playerTank) {
		//move towards player (passes input to pathfinding logic)
		MoveToActor(playerTank, acceptanceRadius); //TODO check radius is in cm
		UE_LOG(LogTemp, Warning, TEXT("MoveToActor called to position: %s"), *playerTank->GetActorLocation().ToString());

		//Aim towards the player
		controlledTank->AimAt(playerTank->GetActorLocation());

		//fire 
		controlledTank->Fire(); //TODO limit firing rate
	}
}