// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <UObject/Interface.h>
#include "ThrustersInterface.generated.h"

UINTERFACE(Blueprintable, BlueprintType)
class OUTERWILDS_API UThrustersInterface : public UInterface
{
	GENERATED_BODY()
};

class OUTERWILDS_API IThrustersInterface
{
	GENERATED_BODY()

public:
	IThrustersInterface() = default;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddPropulsion(const FVector& InPropulsion);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddRotation(const FVector& InRotation);
};
