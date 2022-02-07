// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

FRotator UCharacterFunctionLibrary::makeRotFromFloorAngleInterp(UCapsuleComponent* capsuleComponent, 
	UCharacterMovementComponent* movementComponent, float deltaTime)
{
	FRotator worldRot = capsuleComponent->GetComponentRotation();
	FVector impactNormal = movementComponent->CurrentFloor.HitResult.ImpactNormal;
	FRotator rotFromYZ = UKismetMathLibrary::MakeRotFromYZ(capsuleComponent->GetRightVector(), impactNormal);

	// Replace worldRot.Roll below with rotFromXZ.Roll for adjusting to roll
	// Not needed for 2D game
	FRotator rotFromXZ = UKismetMathLibrary::MakeRotFromXZ(capsuleComponent->GetForwardVector(), impactNormal);

	FRotator target(rotFromYZ.Pitch, worldRot.Yaw, worldRot.Roll);

	return UKismetMathLibrary::RInterpTo(worldRot, target, deltaTime, 10.0f);;
}