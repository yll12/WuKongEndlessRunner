// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "ImpactParticleSystemStruct.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FImpactParticleSystemStruct
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* ObjRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator ImpactDesiredRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector ImpactDesiredLocationOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector ImpactDesiredScale = FVector(1, 1, 1);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* ImpactSoundEffect;

};
