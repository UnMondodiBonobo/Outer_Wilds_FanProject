// Fill out your copyright notice in the Description page of Project Settings.

#include "SolarSystemMediator.h"
#include "OuterWilds/Planets/Sun.h"
#include "OuterWilds/Planets/WaterPlanet.h"
#include "OuterWilds/Utils/FunctionLibraries/GravityUtilsFunctionLibrary.h"

void ASolarSystemMediator::InitializeData()
{
	PlanetFactoryMap.Add(APlanet::StaticClass(), [this](TSubclassOf<APlanet> InPlanetSubclass,
	                     const FVector& InLocation, const FRotator& InRotation) -> APlanet* {
		                     check(GetWorld());
		                     if (!InPlanetSubclass)
		                     {
			                     return nullptr;
		                     }

		                     if (InPlanetSubclass->GetSuperClass() != APlanet::StaticClass())
		                     {
			                     return nullptr;
		                     }

		                     APlanet* NewPlanet = GetWorld()->SpawnActor<APlanet>(
			                     InPlanetSubclass, InLocation, InRotation);
		                     check(NewPlanet);
		                     return NewPlanet;
	                     });

	PlanetFactoryMap.Add(ASun::StaticClass(), [this](TSubclassOf<APlanet> InPlanetSubclass,
	                     const FVector& InLocation, const FRotator& InRotation) -> ASun* {
		                     check(GetWorld());
		                     if (!InPlanetSubclass)
		                     {
			                     return nullptr;
		                     }

		                     if (InPlanetSubclass->GetSuperClass() != ASun::StaticClass())
		                     {
			                     return nullptr;
		                     }

		                     ASun* NewPlanet = GetWorld()->SpawnActor<ASun>(InPlanetSubclass, InLocation, InRotation);
		                     check(NewPlanet);
		                     return NewPlanet;
	                     });

	PlanetFactoryMap.Add(AWaterPlanet::StaticClass(), [this](TSubclassOf<APlanet> InPlanetSubclass,
	                     const FVector& InLocation, const FRotator& InRotation) -> AWaterPlanet* {
		                     check(GetWorld());
		                     if (!InPlanetSubclass)
		                     {
			                     return nullptr;
		                     }

		                     if (InPlanetSubclass->GetSuperClass() != AWaterPlanet::StaticClass())
		                     {
			                     return nullptr;
		                     }

		                     AWaterPlanet* NewPlanet = GetWorld()->SpawnActor<AWaterPlanet>(
			                     InPlanetSubclass, InLocation, InRotation);
		                     check(NewPlanet);
		                     return NewPlanet;
	                     });
}

FPlanetGravitationalDependency ASolarSystemMediator::GetPlanetDataById(const FGuid& InId) const
{
	if (!InId.IsValid())
	{
		return {};
	}

	if (const FPlanetGravitationalDependency* PlanetDataFound = PlanetsDataMap.Find(InId))
	{
		return *PlanetDataFound;
	}

	return {};
}

APlanet* ASolarSystemMediator::SpawnPlanet(TSubclassOf<APlanet> InPlanetSubclass,
	const FVector& InLocation, const FRotator& InRotation)
{
	if (!InPlanetSubclass)
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Warning, TEXT("Planet Subclass passed to %s is not valid"), *GetName());
#endif
		return nullptr;
	}

	if (const auto* FactoryFound = PlanetFactoryMap.Find(InPlanetSubclass->GetSuperClass()))
	{
		return (*FactoryFound)(InPlanetSubclass, InLocation, InRotation);
	}

	return nullptr;
}

FPlanetGravitationalDependency::FPlanetGravitationalDependency(APlanet* InInfluencedPlanet, APlanet* InPivotPlanet) :
	InfluencedPlanet(MakeWeakObjectPtr(InInfluencedPlanet)), PivotPlanet(MakeWeakObjectPtr(InPivotPlanet))
{
}

FPlanetGravitationalDependency::FPlanetGravitationalDependency(APlanet* InInfluencedPlanet) :
	InfluencedPlanet(InInfluencedPlanet)
{
}

ASolarSystemMediator::ASolarSystemMediator()
{
	InitializeData();

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

FGuid ASolarSystemMediator::TryRegisterPlanet(APlanet* InNewPlanet, APlanet* InPivotPlanet)
{
	if (!InNewPlanet)
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Warning, TEXT("InNewPlanet passed to %s is not valid"), *GetName());
#endif
		return {};
	}

	const FGuid Id = FGuid::NewGuid();
	check(Id.IsValid());
	PlanetsDataMap.Add(Id, {InNewPlanet, InPivotPlanet});
	PlanetsData.Add({InNewPlanet, InPivotPlanet});
	return Id;
}

bool ASolarSystemMediator::TryUnregisterPlanet(const FGuid& InId)
{
	if (!InId.IsValid())
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Warning, TEXT("InId Passed to %s is not valid"), *GetName());
#endif

		return false;
	}

	const auto PlanetsDataFound = PlanetsDataMap.FindAndRemoveChecked(InId);
	if (!PlanetsDataFound.IsValid())
	{
		return false;
	}

	if (PlanetsData.Remove(PlanetsDataFound) == 0)
	{
		return false;
	}

	return true;
}

void ASolarSystemMediator::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	for (auto& PlanetData : PlanetsData)
	{
		if (!PlanetData.IsValid())
		{
			continue;
		}

		FVector GravitationalForce = UGravityUtilsFunctionLibrary::ComputeGravitationalForce(
			PlanetData.InfluencedPlanet.Get(),
			PlanetData.PivotPlanet.Get(), PlanetData.InfluencedPlanet->GetPlanetMass(),
			PlanetData.PivotPlanet->GetPlanetMass());

		PlanetData.InfluencedPlanet->ApplyGravitationalForce(GravitationalForce);
		//PlanetData.PivotPlanet->ApplyGravitationalForce(-GravitationalForce);

#if WITH_EDITOR
		DrawDebugLine(GetWorld(), PlanetData.InfluencedPlanet->GetActorLocation(),
		              PlanetData.InfluencedPlanet->GetActorLocation() + GravitationalForce,
		              FColor::Red, false, 0.1, 0, 15);
#endif

		FVector TangentialVelocity = UGravityUtilsFunctionLibrary::ComputeTangentialVelocity(
			PlanetData.InfluencedPlanet.Get(),
			PlanetData.PivotPlanet->GetActorLocation(), PlanetData.PivotPlanet->GetActorRotation().Quaternion(),
			PlanetData.PivotPlanet->GetPlanetMass());

		PlanetData.InfluencedPlanet->
		           ApplyTangentialVelocity(TangentialVelocity + PlanetData.PivotPlanet->GetVelocity());

#if WITH_EDITOR
		DrawDebugLine(GetWorld(), PlanetData.InfluencedPlanet->GetActorLocation(),
		              PlanetData.InfluencedPlanet->GetActorLocation() + TangentialVelocity,
		              FColor::Blue, false, 0.1, 0, 15);
#endif
	}
}
