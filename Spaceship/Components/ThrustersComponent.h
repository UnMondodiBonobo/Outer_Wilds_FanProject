// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <Components/ActorComponent.h>
#include "ThrustersComponent.generated.h"

UENUM(BlueprintType)
enum class EThrustersPropulsionType : uint8
{
	Count UMETA(Hidden),
	Forward,
	Right,
	Up
};

UENUM(BlueprintType)
enum class EThrustersRotationType : uint8
{
	Count UMETA(Hidden),
	Yaw,
	Pitch,
	Roll
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OUTERWILDS_API UThrustersComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UThrustersComponent();

	UFUNCTION(BlueprintCallable, Category = "Thrusters Utility")
	void AddPropulsion(EThrustersPropulsionType InThrustersType, float InInputAxis);

	UFUNCTION(BlueprintCallable, Category = "Thrusters Utility")
	void AddRotation(EThrustersRotationType InThrustersType, float InInputAxis);
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Thrusters Data")
	float ThrustersPropulsionForceMultiplier = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Thrusters Data")
	float ThrustersRotationForceMultiplier = 0.f;

private:
	bool Internal_ThrustersValidityCheck(float InInputAxis) const;
};
