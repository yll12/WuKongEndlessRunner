// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HitReactInterface.h"
#include "DestructibleActorIdle.generated.h"

class UDestructibleComponent;

UCLASS()
class WUKONGENDLESSRUNNER_API ADestructibleActorIdle : public AActor, public IHitReactInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestructibleActorIdle();

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

	/** HitReact System */
	UFUNCTION(BlueprintNativeEvent, BlueprintInternalUseOnly, Category = "HitReactInterface")
		void HitReact(AActor* damageCauser, const struct FImpactParticleSystemStruct& impactParticleSystem);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "HitReactInterface")
		void HitReactSpawnDestructibleActor();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "HitReactInterface")
		void HitReactPlayGetHit(const struct FImpactParticleSystemStruct& impactParticleSystem);

};
