// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelSpawner.generated.h"

class ABaseLevel;
enum class ELevelType : uint8;

UCLASS()
class WUKONGENDLESSRUNNER_API ALevelSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitializeRepeatingLevelsMap();

	TSubclassOf<ABaseLevel> GetNextLevelToSpawn();

	bool isAllSpawnedLevels(ELevelType levelType);

	UPROPERTY()
	TArray<ABaseLevel*> SpawnedLevels;

	TMap<ELevelType, TArray<TSubclassOf<ABaseLevel>>> RepeatingLevelsMap;

	ABaseLevel* LastSpawnedLevel;
	FVector SpawnLocation = FVector();

	// Must be at least 4
	const int MAX_LEVELS_ACTIVE = 6;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABaseLevel> StartingLevelRef;

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<ABaseLevel>> RepeatingLevels;

	UFUNCTION()
		void SpawnLevel(TSubclassOf<ABaseLevel> levelToSpawn);

	void DespawnLevelIfMaxActive();

	UFUNCTION()
		void OnTriggerBoxOverlapBegin(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
