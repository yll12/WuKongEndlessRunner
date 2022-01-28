// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSpawner.h"
#include "BaseLevel.h"
#include "Components/BoxComponent.h"

// Sets default values
ALevelSpawner::ALevelSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelSpawner::BeginPlay()
{
	Super::BeginPlay();

	ABaseLevel* StartingLevel = GetWorld()->SpawnActor<ABaseLevel>(StartingLevelRef,
				FVector(0, 0, 0),
	     		FRotator(0, 0, 0));
	
	StartingLevel->GetNextLevelSpawnTriggerBox()->OnComponentBeginOverlap.AddDynamic(this, &ALevelSpawner::OnTriggerBoxOverlapBegin);

	SpawnLocation = StartingLevel->GetNextLevelSpawnLocation()->GetComponentTransform().GetTranslation();
	UE_LOG(LogTemp, Warning, TEXT("Spawn Location is now %s"), *SpawnLocation.ToString());

//	ABaseLevel* nextLevel = GetWorld()->SpawnActor<ABaseLevel>(RepeatingLevels[0],
//		SpawnLocation,
//		FRotator(0, 0, 0));

//	nextLevel->GetNextLevelSpawnTriggerBox()->OnComponentBeginOverlap.AddDynamic(this, &ALevelSpawner::OnTriggerBoxOverlapBegin);

//	SpawnLocation = nextLevel->GetNextLevelSpawnLocation()->GetComponentTransform().GetTranslation();
//	UE_LOG(LogTemp, Warning, TEXT("Next Location is now %s"), *SpawnLocation.ToString());

//	ABaseLevel* nextLevel2 = GetWorld()->SpawnActor<ABaseLevel>(RepeatingLevels[1],
//		SpawnLocation,
//		FRotator(0, 0, 0));

//	nextLevel2->GetNextLevelSpawnTriggerBox()->OnComponentBeginOverlap.AddDynamic(this, &ALevelSpawner::OnTriggerBoxOverlapBegin);

//	SpawnLocation = nextLevel2->GetNextLevelSpawnLocation()->GetComponentTransform().GetTranslation();
//	UE_LOG(LogTemp, Warning, TEXT("Next Location is now %s"), *SpawnLocation.ToString());



}

// Called every frame
void ALevelSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelSpawner::SpawnLevel() {
	UE_LOG(LogTemp, Warning, TEXT("Next Location is now %s"), *SpawnLocation.ToString());
	UE_LOG(LogTemp, Warning, TEXT("GetWorld? %f"), GetWorld()->GetTimeSeconds());
	ABaseLevel* nextLevel = GetWorld()->SpawnActor<ABaseLevel>(RepeatingLevels[0],
		SpawnLocation,
		FRotator(0, 0, 0));
	if (nextLevel) {
		if (nextLevel->GetNextLevelSpawnTriggerBox()) {
			nextLevel->GetNextLevelSpawnTriggerBox()->OnComponentBeginOverlap.AddDynamic(this, &ALevelSpawner::OnTriggerBoxOverlapBegin);
		}
	}

	SpawnLocation = nextLevel->GetNextLevelSpawnLocation()->GetComponentTransform().GetTranslation();
}

void ALevelSpawner::OnTriggerBoxOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SpawnLevel();
}

