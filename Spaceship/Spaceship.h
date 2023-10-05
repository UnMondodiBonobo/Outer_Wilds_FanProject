// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Pawn.h>

#include "OuterWilds/Planets/GravitationalObjectInterface.h"
#include "Spaceship.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class OUTERWILDS_API ASpaceship : public APawn, public IGravitationalObjectInterface
{
	GENERATED_BODY()

public:
	ASpaceship();

	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	virtual void BeginPlay() override;

	/*Gravitational Object Interface functions implementation*/
	UFUNCTION(BlueprintNativeEvent)
	float GetPlanetMass() const;
	UFUNCTION(BlueprintNativeEvent)
	void ApplyGravitationalForce(const FVector& InForce);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spaceship Components")
	TObjectPtr<UStaticMeshComponent> Body;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spaceship Components")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spaceship Components")
	TObjectPtr<UCameraComponent> Camera;
};

inline float ASpaceship::GetPlanetMass_Implementation() const
{
	return Body->GetMass();
}

