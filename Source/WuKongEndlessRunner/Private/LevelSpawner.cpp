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
	SpawnLevel(StartingLevelRef);

}

// Called every frame
void ALevelSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALevelSpawner::SpawnLevel(TSubclassOf<ABaseLevel> levelToSpawn) {
	nextLevel = GetWorld()->SpawnActor<ABaseLevel>(levelToSpawn, SpawnLocation, FRotator(0, 0, 0));
	if (nextLevel) {
		nextLevel->GetNextLevelSpawnTriggerBox()->OnComponentBeginOverlap.AddDynamic(this, &ALevelSpawner::OnTriggerBoxOverlapBegin);
		SpawnLocation = nextLevel->GetNextLevelSpawnLocation()->GetComponentTransform().GetTranslation();
		SpawnedLevels.Emplace(nextLevel);
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
	
	TMap<ELevelType, TArray<TSubclassOf<ABaseLevel>>> RepeatingLevelsMap;
	for (ELevelType levelType : AllLevelTypes) {
		UE_LOG(LogClass, Log, TEXT("Test"));
		TMap<ELevelType, FString> FruitMap;
		FruitMap.Add(levelType, TEXT("Pineapple"));
		UE_LOG(LogClass, Log, TEXT("Test enum: %s"), *FruitMap[levelType]);

		
		RepeatingLevelsMap.Add(levelType, {});
	}

	
	for (TSubclassOf<ABaseLevel> level : RepeatingLevels) {
		ELevelType levelType = level->GetDefaultObject<ABaseLevel>()->LevelType;
		RepeatingLevelsMap[levelType].Add(level);
		UE_LOG(LogClass, Log, TEXT("Testing: %s!"), *RepeatingLevelsMap[levelType][0]->GetName());
	}
	int32 levelToSpawn;

	switch (nextLevel->LevelType) {
	case ELevelType::Slope:
		UE_LOG(LogClass, Log, TEXT("Inside slope!"));
		levelToSpawn = FMath::RandRange(0, RepeatingLevelsMap[ELevelType::Flat].Num() - 1);
		nextLevel->GetNextLevelSpawnTriggerBox()->DestroyComponent();
		SpawnLevel(RepeatingLevelsMap[ELevelType::Flat][levelToSpawn]);
		break;
	case ELevelType::Flat:
		UE_LOG(LogClass, Log, TEXT("Inside Flat!"));
		levelToSpawn = FMath::RandRange(0, RepeatingLevels.Num() - 1);
		nextLevel->GetNextLevelSpawnTriggerBox()->DestroyComponent();
		SpawnLevel(RepeatingLevels[levelToSpawn]);
	}

	
}

