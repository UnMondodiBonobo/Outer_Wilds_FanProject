// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <Components/SphereComponent.h>
#include "AtmosphereGravityComponent.generated.h"

class IGravitationalObjectInterface;
class USphereComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGravitationForceChangedDelegate, const FVector&, AppliedForce);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OUTERWILDS_API UAtmosphereGravityComponent : public USphereComponent
{
	GENERATED_BODY()

public:	
	UAtmosphereGravityComponent();
	
	UFUNCTION(BlueprintCallable, Category = "Gravity Component Data setter")
	void SetCenterLocation(const FVector& InCenterLocation);
	UFUNCTION(BlueprintPure, Category = "Gravity Component Data getter")
	const FVector& GetCenterLocation() const;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FOnGravitationForceChangedDelegate OnGravitationForceChanged;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Gravity Component Data")
	FVector GravityCenterLocation;
};

inline const FVector& UAtmosphereGravityComponent::GetCenterLocation() const
{
	return GravityCenterLocation;
}