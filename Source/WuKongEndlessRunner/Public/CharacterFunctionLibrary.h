// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CharacterFunctionLibrary.generated.h"

class UCapsuleComponent;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class WUKONGENDLESSRUNNER_API UCharacterFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintPure, Category = "Test")
	static FRotator makeRotFromFloorAngleInterp(UCapsuleComponent* capsuleComponent, UCharacterMovementComponent* movementComponent, float deltaTime );
};
