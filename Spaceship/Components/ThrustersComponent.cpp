// Fill out your copyright notice in the Description page of Project Settings.

#include "ThrustersComponent.h"
#include "OuterWilds/Interfaces/ThrustersInterface.h"

UThrustersComponent::UThrustersComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UThrustersComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UThrustersComponent::Internal_ThrustersValidityCheck(float InInputAxis) const
{
	check(GetOwner());
	if (!GetOwner()->Implements<UThrustersInterface>())
	{
		return false;
	}

	if (InInputAxis == 0.f)
	{
		return false;
	}

	return true;
}

void UThrustersComponent::AddPropulsion(EThrustersPropulsionType InThrustersType, float InInputAxis)
{
	if (!Internal_ThrustersValidityCheck(InInputAxis))
	{
		return;
	}

	FVector Force{ForceInitToZero};
	switch (InThrustersType)
	{
	case EThrustersPropulsionType::Count:
		break;

	case EThrustersPropulsionType::Forward:
		Force = GetOwner()->GetActorForwardVector() * ThrustersPropulsionForceMultiplier * InInputAxis;
		break;

	case EThrustersPropulsionType::Right:
		Force = GetOwner()->GetActorRightVector() * ThrustersPropulsionForceMultiplier * InInputAxis;
		break;

	case EThrustersPropulsionType::Up:
		Force = GetOwner()->GetActorUpVector() * ThrustersPropulsionForceMultiplier * InInputAxis;
		break;

	default:
		break;
	}

	IThrustersInterface::Execute_AddPropulsion(GetOwner(), Force);
}

void UThrustersComponent::AddRotation(EThrustersRotationType InThrustersType, float InInputAxis)
{
	if (!Internal_ThrustersValidityCheck(InInputAxis))
	{
		return;
	}

	FVector AngularImpulse{ForceInitToZero};
	switch (InThrustersType)
	{
	case EThrustersRotationType::Count:
		break;

	case EThrustersRotationType::Yaw:
		AngularImpulse = FRotationMatrix(GetOwner()->GetActorRotation()).GetScaledAxis(EAxis::Z) *
			ThrustersRotationForceMultiplier * InInputAxis;
		break;

	case EThrustersRotationType::Pitch:
		AngularImpulse = FRotationMatrix(GetOwner()->GetActorRotation()).GetScaledAxis(EAxis::Y) * -1.f *
			ThrustersRotationForceMultiplier * InInputAxis;
		break;

	case EThrustersRotationType::Roll:
		AngularImpulse = FRotationMatrix(GetOwner()->GetActorRotation()).GetScaledAxis(EAxis::X) * -1.f *
			ThrustersRotationForceMultiplier * InInputAxis;
		break;
	}

	IThrustersInterface::Execute_AddRotation(GetOwner(), AngularImpulse);
}
