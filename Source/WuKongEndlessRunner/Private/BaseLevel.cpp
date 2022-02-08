// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLevel.h"
#include "Components/BoxComponent.h"
#include "Engine.h"

// Sets default values
ABaseLevel::ABaseLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootSceneComponent->SetupAttachment(RootComponent);
	RootComponent = RootSceneComponent;

	NextLevelSpawnTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("NextLevelSpawnTriggerBox"));
	NextLevelSpawnTriggerBox->SetupAttachment(RootSceneComponent);

	NextLevelSpawnLocation = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnLocation"));
	NextLevelSpawnLocation->SetupAttachment(RootSceneComponent);
	
	BackTrackBlocker = CreateDefaultSubobject<UBoxComponent>(TEXT("BackTrackBlocker"));
	BackTrackBlocker->SetupAttachment(RootSceneComponent);

}

// Called when the game starts or when spawned
void ABaseLevel::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
