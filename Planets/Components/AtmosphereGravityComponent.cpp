// Fill out your copyright notice in the Description page of Project Settings.

#include "OuterWilds/Planets/Components/AtmosphereGravityComponent.h"
#include "OuterWilds/Planets/GravitationalObjectInterface.h"
#include "OuterWilds/Utils/FunctionLibraries/GravityUtilsFunctionLibrary.h"

UAtmosphereGravityComponent::UAtmosphereGravityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UAtmosphereGravityComponent::SetCenterLocation(const FVector& InCenterLocation)
{
	GravityCenterLocation = InCenterLocation;
}

void UAtmosphereGravityComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	check(GetOwner());
	
	if (!GetOwner()->Implements<UGravitationalObjectInterface>())
	{
		return;
	}

	for (auto* OverlappingActor : OverlappingActors)
	{
		if (!OverlappingActor->Implements<UGravitationalObjectInterface>())
		{
			continue;
		}

		const FVector GravitationalForce = UGravityUtilsFunctionLibrary::ComputeGravitationalForce(
			OverlappingActor, GetOwner(),
			IGravitationalObjectInterface::Execute_GetPlanetMass(OverlappingActor),
			IGravitationalObjectInterface::Execute_GetPlanetMass(GetOwner()));

		IGravitationalObjectInterface::Execute_ApplyGravitationalForce(OverlappingActor, GravitationalForce);
	}
}
