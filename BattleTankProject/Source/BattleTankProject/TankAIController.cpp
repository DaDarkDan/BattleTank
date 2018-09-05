// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	ATank* controlledTank = GetControlledTank();

	if(!controlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController not possessing a Tank"));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AIController possessing %s"), *controlledTank->GetName());
	}

	ATank* firstPlayerTank = GetPlayerTank();

	if(!firstPlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController cannot find first player."));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AIController found player: %s"), *firstPlayerTank->GetName());
	}
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(GetControlledTank()) {
		//TODO move towards player

		//Aim towards the player
		GetControlledTank()->aimtAt(GetPlayerTank()->GetActorLocation());

		//fire if ready
	}
}


ATank* ATankAIController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {

	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}



