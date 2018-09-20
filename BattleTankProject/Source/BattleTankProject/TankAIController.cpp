// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	AActor* playerActor = GetWorld()->GetFirstPlayerController()->GetPawn();

	if(!ensure(playerTank && GetPawn())) { return; }
	//move towards player (passes input to pathfinding logic)
	MoveToActor(playerActor, acceptanceRadius); //TODO check radius is in cm

	auto aimingComp = GetPawn()->FindComponentByClass<UTankAimingComponent>(); //TODO refactor this to constructor
	if(!ensure(aimingComp)) { return; }
	//Aim towards the player
	aimingComp->AimAt(playerActor->GetActorLocation());

	aimingComp->Fire(); //TODO limit firing rate
}