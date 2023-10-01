// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include "GravitationalObjectInterface.generated.h"

UINTERFACE(Blueprintable, BlueprintType)
class OUTERWILDS_API UGravitationalObjectInterface : public UInterface
{
	GENERATED_BODY()
};

class OUTERWILDS_API IGravitationalObjectInterface 
{
	GENERATED_BODY()

public:
	IGravitationalObjectInterface() = default;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float GetPlanetMass() const;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ApplyGravitationalForce(const FVector& InForce);
};
