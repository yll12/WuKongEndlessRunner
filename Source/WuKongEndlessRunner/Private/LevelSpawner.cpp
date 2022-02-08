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
	}
	SpawnedLevels.Emplace(nextLevel);

	for (int32 b = 0; b < SpawnedLevels.Num(); b++)
	{
		UE_LOG(LogClass, Log, TEXT("Names: %s"), *(SpawnedLevels[b]->GetName()));
	}

	UE_LOG(LogClass, Log, TEXT("End"));

	if (SpawnedLevels.Num() > 6) {
		SpawnedLevels[0]->Destroy();
		SpawnedLevels.RemoveAt(0);
		SpawnedLevels[1]->GetBackTrackBlocker()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	}
}

void ALevelSpawner::OnTriggerBoxOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	int32 levelToSpawn = FMath::RandRange(0, RepeatingLevels.Num() - 1);
	nextLevel->GetNextLevelSpawnTriggerBox()->DestroyComponent();
	SpawnLevel(RepeatingLevels[levelToSpawn]);
}

