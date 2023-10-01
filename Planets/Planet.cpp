// Fill out your copyright notice in the Description page of Project Settings.

#include "Planet.h"
#include <Components/SphereComponent.h>

APlanet::APlanet()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
}

void APlanet::ApplyGravitationalForce_Implementation(const FVector& InForce)
{
	if(InForce.IsZero())
	{
		return;
	}
	
	Mesh->AddForce(InForce);
}

void APlanet::ApplyTangentialVelocity(const FVector& InTangentialVelocity)
{
	if(InTangentialVelocity.IsZero())
	{
		return;
	}
	
	Mesh->SetPhysicsLinearVelocity(InTangentialVelocity);
}

void APlanet::BeginPlay()
{
	Super::BeginPlay();

	// check(Mesh);
	// Mesh->SetSimulatePhysics(true);
	// Mesh->SetEnableGravity(false);
	Coordinates = GetActorTransform().GetLocation();
	Rotate();
}

void APlanet::Rotate()
{
	
#if WITH_EDITOR
	if(DeltaRotation == FVector::ZeroVector)
	{
		UE_LOG(LogTemp, Warning, TEXT("Delta Rotation passed to %s is Zero, %s will not rotate"), *GetName(), *GetName());
	}
#endif
	
	check(Mesh);
	Mesh->AddAngularImpulseInRadians(DeltaRotation, NAME_None, true);
}

