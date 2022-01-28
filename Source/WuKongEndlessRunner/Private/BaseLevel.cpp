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

//	levelSpawner = CreateDefaultSubobject<ATesting>(TEXT("LevelSpawner"));

}

// Called when the game starts or when spawned
void ABaseLevel::BeginPlay()
{
	Super::BeginPlay();
//	GetWorld()->SpawnActor<ABaseLevel>(Level1,
//		FVector(1000.0f, 0, 0.0f),
//		FRotator(0, 90, 0), SpawnInfo);
//	UE_LOG(LogTemp, Warning, TEXT("Starting!!"));
//	SpawnLocation = FVector(1000.0f, 0, 0.0f);
//	SpawnRotation = FRotator(0, 0, 0);
//	levelSpawner->SpawnLevel(Level1);
//	UE_LOG(LogTemp, Warning, TEXT("Spawn complete!!"));
//	NextLevelSpawnTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseLevel::OnTriggerBoxOverlapBegin);
	
}

// Called every frame
void ABaseLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseLevel::OnTriggerBoxOverlapBegin(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
//	UE_LOG(LogTemp, Warning, TEXT("Overlapped!"));
//	UE_LOG(LogTemp, Warning, TEXT("Overlapped %s"), "Test");
//	UE_LOG(LogTemp, Warning, TEXT("Overlapped %s"), *LevelManagerRef->LevelList[0]->GetClass()->GetFName().ToString());
//	UE_LOG(LogTemp, Warning, TEXT("Overlapped %s"), *Level1->GetClass()->GetFName().ToString());
//	UE_LOG(LogTemp, Warning, TEXT("Overlapped %s"), *NextLevelSpawnLocation->GetComponentTransform().GetTranslation().ToString());
//	GetWorld()->GetRealTimeSeconds();
//	levelSpawner->SpawnLevel(Level1);
//	levelSpawner->SpawnLevel();
//	GetWorld()->SpawnActor<ABaseLevel>(Level1,
//		FVector(1000.0f, 0, 0.0f),
//		FRotator(0, 90, 0), SpawnInfo);

//	GetWorld()->SpawnActor<ABaseLevel>(Level1,
//		NextLevelSpawnLocation->GetComponentTransform().GetTranslation(),
//		FRotator(0, 90, 0), SpawnInfo);

//	NextLevelSpawnTriggerBox->DestroyComponent();
}

