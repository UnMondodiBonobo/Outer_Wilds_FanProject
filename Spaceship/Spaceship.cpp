// Fill out your copyright notice in the Description page of Project Settings.

#include "OuterWilds/Spaceship/Spaceship.h"
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>

ASpaceship::ASpaceship()
{
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Component"));
	SetRootComponent(Body);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm Component"));
	SpringArm->SetupAttachment(GetRootComponent());
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	Camera->SetupAttachment(SpringArm);
}

void ASpaceship::BeginPlay()
{
	Super::BeginPlay();
}

void ASpaceship::AddRotation_Implementation(const FVector& InRotation)
{
	if(InRotation.IsZero())
	{
		return;
	}

	Body->AddAngularImpulseInDegrees(InRotation);
}

void ASpaceship::AddPropulsion_Implementation(const FVector& InPropulsion)
{
	if(InPropulsion.IsZero())
	{
		return;
	}
	
	Body->AddForce(InPropulsion);
}

void ASpaceship::ApplyGravitationalForce_Implementation(const FVector& InForce)
{
	if(InForce.IsZero())
	{
		return;
	}
	
	Body->AddForce(InForce);
}

void ASpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

