// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>
#include "GravitationalObjectInterface.h"
#include "Planet.generated.h"

class USphereComponent;

UCLASS()
class OUTERWILDS_API APlanet : public AActor, public IGravitationalObjectInterface
{
	GENERATED_BODY()
	
public:	
	APlanet();

	/*Get absolute spatial coordinates of the planet*/
	UFUNCTION(BlueprintPure, Category = "Planet Data")
	const FVector& GetCoordinates() const;

	/*Gravitational Object Interface functions implementation*/
	UFUNCTION(BlueprintNativeEvent)
	float GetPlanetMass() const;
	UFUNCTION(BlueprintNativeEvent)
	void ApplyGravitationalForce(const FVector& InForce);

	void ApplyTangentialVelocity(const FVector& InTangentialVelocity);

protected:
	virtual void BeginPlay() override;
	
	/*Basic Planet rotation around its internal axis*/
	void Rotate();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(EditAnywhere, Category = "Rotation Data")
	FVector DeltaRotation {FVector::ZeroVector};

	FVector Coordinates {FVector::ZeroVector};
};

inline const FVector& APlanet::GetCoordinates() const
{
	return Coordinates;
}

inline float APlanet::GetPlanetMass_Implementation() const
{
	return Mesh->GetMass();
}
