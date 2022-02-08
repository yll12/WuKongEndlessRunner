// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSpawner.h"
#include "BaseLevel.h"
#include "Components/BoxComponent.h"

// Sets default values
ALevelSpawner::ALevelSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ALevelSpawner::BeginPlay()
{
	Super::BeginPlay();
	InitializeRepeatingLevelsMap();
	SpawnLevel(StartingLevelRef);
	SpawnLevel(RandomLevel());

}

void ALevelSpawner::InitializeRepeatingLevelsMap()
{
	for (ELevelType levelType : AllLevelTypes) {
		RepeatingLevelsMap.Add(levelType, {});
	}

	for (TSubclassOf<ABaseLevel> level : RepeatingLevels) {
		ELevelType levelType = level->GetDefaultObject<ABaseLevel>()->LevelType;
		RepeatingLevelsMap[levelType].Add(level);
	}
}

// Called every frame
void ALevelSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALevelSpawner::SpawnLevel(TSubclassOf<ABaseLevel> levelToSpawn) {
	if (LastSpawnedLevel) {
		LastSpawnedLevel->GetNextLevelSpawnTriggerBox()->DestroyComponent();
	}

	LastSpawnedLevel = GetWorld()->SpawnActor<ABaseLevel>(levelToSpawn, SpawnLocation, FRotator(0, 0, 0));
	if (LastSpawnedLevel) {
		LastSpawnedLevel->GetNextLevelSpawnTriggerBox()->OnComponentBeginOverlap.AddDynamic(this, &ALevelSpawner::OnTriggerBoxOverlapBegin);
		SpawnLocation = LastSpawnedLevel->GetNextLevelSpawnLocation()->GetComponentTransform().GetTranslation();
		SpawnedLevels.Emplace(LastSpawnedLevel);
	}
	DespawnLevelIfMaxActive();
}

void ALevelSpawner::DespawnLevelIfMaxActive()
{
	if (SpawnedLevels.Num() > MAX_LEVELS_ACTIVE) {
		SpawnedLevels[0]->Destroy();
		SpawnedLevels.RemoveAt(0);

		// Activate backtrack blocker
		SpawnedLevels[1]->GetBackTrackBlocker()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	}
}

void ALevelSpawner::OnTriggerBoxOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SpawnLevel(GetNextLevelToSpawn());
}

TSubclassOf<ABaseLevel> ALevelSpawner::GetNextLevelToSpawn()
{
	if (isAllSpawnedLevels(ELevelType::Flat)) {
		return RandomLevel(ELevelType::Slope);;
	}
	switch (LastSpawnedLevel->LevelType) {
		case ELevelType::Slope:
			// Random Flat level next (no two slope level consecutively)
			return RandomLevel(ELevelType::Flat);
			break;
		case ELevelType::Flat:
			return RandomLevel();
	}

	return RandomLevel();
}

TSubclassOf<ABaseLevel> ALevelSpawner::RandomLevel(ELevelType levelType) 
{
	return RepeatingLevelsMap[levelType][FMath::RandRange(0, RepeatingLevelsMap[levelType].Num() - 1)];
}

TSubclassOf<ABaseLevel> ALevelSpawner::RandomLevel()
{
	return RepeatingLevels[FMath::RandRange(0, RepeatingLevels.Num() - 1)];
}

bool ALevelSpawner::isAllSpawnedLevels(ELevelType levelType)
{
	// Is there a Java allMatch() equivalent?
	for (ABaseLevel* level : SpawnedLevels) {
		if (level->LevelType != levelType) {
			return false;
		}
	}
	return true;
}

