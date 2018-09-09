// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Engine/Classes/GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	projectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));
	projectileMovementComp->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float speed) {
	projectileMovementComp->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	projectileMovementComp->Activate();
}