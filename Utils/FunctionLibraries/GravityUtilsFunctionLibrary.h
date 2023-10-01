// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintFunctionLibrary.h>
#include "GravityUtilsFunctionLibrary.generated.h"

class APlanet;

UCLASS()
class OUTERWILDS_API UGravityUtilsFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	/**@brief Function that computes gravitational force
	 *
	 * @param InFirstMass Mass of the first object in kg
	 * @param InSecondMass Mass of the second object in kg
	 * @param InRadius Distance between the two objects in meters
	 *
	 * @return Gravitational force as: Newtonian force
	 */
	UFUNCTION(BlueprintPure, Category = "Gravity Utils")
	static float ComputeGravitationalForceMagnitude(const double& InFirstMass, const double& InSecondMass, float InRadius);
	
	/**@brief Function that computes gravitational force as normalized vector * magnitude between two objects
	 *
	 * @param InFirstActor First Actor primitive component
	 * @param InSecondActor Second Actor primitive component
	 * @param InFirstActorMass First Actor mass
	 * @param InSecondActorMass Second Actor mass
	 *
	 * @return Gravitational force as: Vector direction * force magnitude 
	 */
	UFUNCTION(BlueprintPure, Category = "Gravity Utils")
	static FVector ComputeGravitationalForce(const AActor* InFirstActor, const AActor* InSecondActor,
		const double& InFirstActorMass, const double& InSecondActorMass);

	/**
	 * @brief Function that computes an actor tangential velocity depending on mass and radius from pivot
	 *
	 * @param InPivotActorMass Mass of the moving actor
	 * @param InRadius Radius between the moving actor and the pivot
	 *
	 * @return Tangential velocity as: velocity magnitude
	 */
	UFUNCTION(BlueprintPure, Category = "Gravity Utils")
	static float ComputeTangentialVelocityMagnitude(const double& InPivotActorMass, float InRadius);

	/**
	 * @brief Function that computes an actor tangential velocity * vector depending on mass and radius from pivot 
	 * 
	 * @param InMovingActor Moving actor
	 * @param InPivotLocation Center Pivot location
	 * @param InPivotRotation Center Pivot rotation
	 * @param InPivotMass Moving Actor mass
	 * 
	 * @return Tangential velocity as: tangential vector * magnitude
	 */
	UFUNCTION(BlueprintPure, Category = "Gravity Utils")
	static FVector ComputeTangentialVelocity(const AActor* InMovingActor, const FVector& InPivotLocation,
		const FQuat& InPivotRotation, const double& InPivotMass);
	
	static constexpr float GravitationalConstant = 1000000.f;
};