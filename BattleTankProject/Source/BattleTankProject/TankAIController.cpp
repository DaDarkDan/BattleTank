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
		//TODO move towards player

		//Aim towards the player
		controlledTank->AimAt(playerTank->GetActorLocation());

		//fire 
		controlledTank->Fire(); //TODO limit firing rate
	}
}