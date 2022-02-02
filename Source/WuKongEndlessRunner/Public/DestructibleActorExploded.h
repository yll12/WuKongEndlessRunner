// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleActorExploded.generated.h"

class USceneComponent;
class UDestructibleComponent;

UCLASS()
class WUKONGENDLESSRUNNER_API ADestructibleActorExploded : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestructibleActorExploded();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void DestroyActorAfterDelay(float delay);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* RootSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UDestructibleComponent* DestructibleComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
