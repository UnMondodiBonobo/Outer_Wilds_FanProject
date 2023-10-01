// Fill out your copyright notice in the Description page of Project Settings.

#include "OuterWilds/Utils/FunctionLibraries/GravityUtilsFunctionLibrary.h"

float UGravityUtilsFunctionLibrary::ComputeGravitationalForceMagnitude(const double& InFirstMass,
	const double& InSecondMass, float InRadius)
{
	return (GravitationalConstant * InFirstMass * InSecondMass) / FMath::Pow(InRadius, 2);
}

FVector UGravityUtilsFunctionLibrary::ComputeGravitationalForce(const AActor* InFirstActor,
	const AActor* InSecondActor, const double& InFirstActorMass, const double& InSecondActorMass)
{
	if (!InFirstActor)
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Warning, TEXT("First Actor passed to Gravity Utils Function Library"
			       "is not valid"));
#endif

		return {};
	}

	if (!InSecondActor)
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Warning, TEXT("Second Actor passed to Gravity Utils Function Library"
			       "is not valid"));
#endif

		return {};
	}

	if (InFirstActorMass <= 0.00)
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Warning, TEXT("First Actor %s mass: %f passed to Gravity Utils Function Library"
			       "is not valid, the value must be greater than 0"), *InFirstActor->GetName(), InFirstActorMass);
#endif

		return {};
	}

	if (InSecondActorMass <= 0.00)
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Warning, TEXT("Second Actor %s mass: %f passed to Gravity Utils Function Library"
			       "is not valid, the value must be greater than 0"), *InSecondActor->GetName(), InSecondActorMass);
#endif

		return {};
	}

	FVector RelativeLocation = InSecondActor->GetActorLocation() - InFirstActor->GetActorLocation();
	const float DistanceRadius = RelativeLocation.Size();
	const float GravitationalForceMagnitude = ComputeGravitationalForceMagnitude(
		InFirstActorMass, InSecondActorMass, DistanceRadius);
	RelativeLocation.Normalize();
	return RelativeLocation * GravitationalForceMagnitude;
}

float UGravityUtilsFunctionLibrary::ComputeTangentialVelocityMagnitude(const double& InPivotActorMass, float InRadius)
{
	return FMath::Sqrt(GravitationalConstant * InPivotActorMass / InRadius);
}

FVector UGravityUtilsFunctionLibrary::ComputeTangentialVelocity(const AActor* InMovingActor,
	const FVector& InPivotLocation, const FQuat& InPivotRotation, const double& InPivotMass)
{
	if (!InMovingActor)
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Warning, TEXT("Moving Actor passed to Gravity Utils Function Library"
			       "is not valid"));
#endif

		return {};
	}

	const FVector RelativeLocation = InMovingActor->GetActorLocation() - InPivotLocation;
	const FVector TangentialVectorDirection = FVector::CrossProduct(RelativeLocation.GetSafeNormal(),
	                                                                InPivotRotation.GetUpVector()).GetSafeNormal();

	return ComputeTangentialVelocityMagnitude(InPivotMass, RelativeLocation.Size()) *
		TangentialVectorDirection;
}
