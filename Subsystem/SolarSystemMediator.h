// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>
#include "SolarSystemMediator.generated.h"

class APlanet;

/* Struct that represent a pair of planets: influenced planet rotates around the pivot planet;
 * this is done to avoid multiple gravitational forces between all the planets since that would require
 * an infinite tuning time for planets masses, distances and radius
 */
USTRUCT(BlueprintType)
struct FPlanetGravitationalDependency
{
	GENERATED_BODY()

	FPlanetGravitationalDependency() = default;
	
	/*Parametrized Constructors, Initialization list is handled in .cpp since is not necessary to include extra .h files in here*/
	FPlanetGravitationalDependency(APlanet* InInfluencedPlanet, APlanet* InPivotPlanet);
	explicit FPlanetGravitationalDependency(APlanet* InInfluencedPlanet);

	bool IsValid() const
	{
		return PivotPlanet.IsValid() && InfluencedPlanet.IsValid();
	}

	bool operator == (const FPlanetGravitationalDependency& InOther) const
	{
		if(IsValid() && InOther.IsValid())
		{
			return PivotPlanet == InOther.PivotPlanet && InfluencedPlanet == InOther.InfluencedPlanet;
		}
		
		return false;
	}

	TWeakObjectPtr<APlanet> InfluencedPlanet;
	TWeakObjectPtr<APlanet> PivotPlanet;
};

UCLASS(Blueprintable, BlueprintType)
class OUTERWILDS_API ASolarSystemMediator : public AActor
{
	GENERATED_BODY()

public:
	ASolarSystemMediator();

	/**
	 * @brief Function that registers and stores planets data 
	 * @param InNewPlanet New influenced planet to register
	 * @param InPivotPlanet New Pivot planet to register
	 * @return Planet new Id
	 */
	UFUNCTION(BlueprintCallable, Category = "Planet Registration")
	FGuid TryRegisterPlanet(APlanet* InNewPlanet, APlanet* InPivotPlanet = nullptr);

	/**
	 * @brief Function that unregister planets data by Id
	 * @param InId Planet data Id to remove
	 * @return true if successful, false otherwise
	 */
	UFUNCTION(BlueprintCallable, Category = "Planet Registration")
	bool TryUnregisterPlanet(const FGuid& InId);

	/**
	 * @brief Function that returns PlanetsData by Id, returns a copy since BP is unable to handle custom struct pointers
	 * @param InId Id of the planet data to search for 
	 * @return Planets Data found
	 */
	UFUNCTION(BlueprintPure, Category = "Planet Registration")
	FPlanetGravitationalDependency GetPlanetDataById(const FGuid& InId) const;
	
	/**
	 * @brief Planet Factory function to create any Planet type 
	 * @param InPlanetSubclass Planet TSubclassOf to spawn
	 * @param InLocation Optional planet location spawn point
	 * @param InRotation Optional planet spawn rotation
	 *
	 * @return Pointer to the spawned planet
	 */
	UFUNCTION(BlueprintCallable, Category = "Planet Creation", meta = (AdvancedDisplay = 1))
	APlanet* SpawnPlanet(TSubclassOf<APlanet> InPlanetSubclass,
		const FVector& InLocation = FVector::ZeroVector, const FRotator& InRotation = FRotator::ZeroRotator);
	
	virtual void Tick(float DeltaSeconds) override;

private:
	/*Initialization Function called by constructor*/
	void InitializeData();

	/*Factory Map to avoid multiple inherited factory UObject*/
	TMap<TWeakObjectPtr<UClass>, TFunction<APlanet*(TSubclassOf<APlanet> InPlanetSubclass,
		const FVector& InLocation, const FRotator& InRotation)>> PlanetFactoryMap;

	/*Stored planet data for fast access O(1)*/
	UPROPERTY()
	TMap<FGuid, FPlanetGravitationalDependency> PlanetsDataMap;

	/*Stored planet data for "fast" iteration O(n) worst case*/
	UPROPERTY()
	TArray<FPlanetGravitationalDependency> PlanetsData;
};
